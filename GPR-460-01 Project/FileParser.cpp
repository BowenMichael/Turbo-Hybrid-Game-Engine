#include "FileParser.h"


#include <fstream>
#include <vector>
#include <iostream>

const char* gameObjectTag = "GameObject_0";

int charsToIntLiteral(const unsigned char* a)
{
	return ((a[0] * 256 + a[1]) * 256 + a[2]) * 256 + a[3];
}

Turbohybrid::FileParser::FileParser(const TurboHybrid::string& fileName):
	mFileName(fileName)
{
	std::ifstream f(fileName.c_str());
	mData = json::parse(f);
	/*mData = json::parse(R"(
		{
			"GameObjects" :
			[
				{
					"TRAN": [0, 0], 
					"RECT": 
					{
						"Size": [100, 100],
						"Color": [1, 0, 1, 1]
					},
					"CLID" : {},
					"ZCCR" : 
					{
						"Color": [1, 1, 0, 1]
					},
					"PLRC" : {}

				},
				{
					"TRAN": [220, 110], 
					"RECT": 
					{
						"Size": [150, 100],
						"Color": [1, 0, 1, 1]
					},
					"CLID" : {}
				}

			]
		}	
	)");*/
}

void Turbohybrid::FileParser::LoadTransformData(TurboHybrid::Transform* transform, const json& data)
{
	std::vector<int> position = {};
	data.get_to(position);
	//std::cout << "(" << position[0] << ", " << position[1] << ")" << "\n";
	transform->load(TurboHybrid::Vector3(position[0], position[1], 0));
}

void Turbohybrid::FileParser::LoadRectData(TurboHybrid::RectangleRenderer* rectRend, const json& data)
{
	std::vector<int> rect = {};
	std::vector<float> color = {};
	data.at("Size").get_to(rect);
	data.at("Color").get_to(color);

	rectRend->load(Rect(rect[0], rect[1]), Color(color[0], color[1], color[2], color[3]));


}

void Turbohybrid::FileParser::LoadColliderData(TurboHybrid::RectangleCollider* collider, const json& data)
{
	collider->load();
}

void Turbohybrid::FileParser::LoadPlayerControllerData(TurboHybrid::PlayerController* plr, const json& data)
{
	plr->load();
}

void Turbohybrid::FileParser::LoadColorColliderData(TurboHybrid::ColliderColorChanger* cccr, const json& data)
{
	std::vector<float> color = {};
	data.at("Color").get_to(color);
	cccr->load(Color(color[0], color[1], color[2], color[3]));
}

size_t Turbohybrid::FileParser::GetNumOfGameObjects()
{
	return mData.at("GameObjects").size();
}

void Turbohybrid::FileParser::DeserializeGameobject(TurboHybrid::GameObject* gameObject, int index, TurboHybrid::ComponentSystem* allocator)
{
	int numOfComponents = GetGameObject(index).size();
	json gameobject = GetGameObject(index);
	for (json::iterator it = gameobject.begin(); it != gameobject.end(); ++it) {
		if ((int)it.key().size() == 4) {
			Uint32 i = charsToIntLiteral((unsigned char*)(it.key().c_str()));
			allocator->AddComponentToGameObject(i, gameObject);
			std::cout << it.key() << ", " << it.key().c_str() << " : " << it.value() << "\n";

			switch (i) {
			case TurboHybrid::Transform::kCompID:
				LoadTransformData(gameObject->GetTransform(), it.value());
				break;
			case TurboHybrid::RectangleRenderer::kCompID:
				LoadRectData(gameObject->GetRenderer(), it.value());
				break;
			case TurboHybrid::RectangleCollider::kCompID:
				LoadColliderData(gameObject->GetCollider(), it.value());
				break;
			case TurboHybrid::PlayerController::kCompID:
				LoadPlayerControllerData(gameObject->GetPlayerController(), it.value());
				break;
			case TurboHybrid::ColliderColorChanger::kCompID:
				LoadColorColliderData(gameObject->GetColorChanger(), it.value());
				break;
			default:
				break;

			}
		}
		else {
			std::cout << "KEY IS NOT 4 CHAR" << "\n";
		}

	}

}

json Turbohybrid::FileParser::GetGameObject(int id)
{
	return mData.at("GameObjects").at(id);
}

bool Turbohybrid::FileParser::hasComponent(const json& gameobject, const std::string& id)
{
	if (gameobject.contains(id)) {
		return true;
	}
	return false;
}

TurboHybrid::Vector3 Turbohybrid::FileParser::ParseGameObjectPositionData(const json& gameObject)
{

	return TurboHybrid::Vector3();
}
