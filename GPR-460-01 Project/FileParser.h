#pragma once
#include "headers/System_Common.h"
#include "json/single_include/nlohmann/json.hpp" //Using https://github.com/nlohmann/json#read-json-from-a-file
#include "headers/Util/Vector3.h"
#include <headers/Components/Component_System.h>
#include <headers/GameObject.h>
using json = nlohmann::json;

namespace Turbohybrid 
{
	/*class GameObject;
	class ComponentSystem;*/
	class FileParser
	{
	public:
		FileParser(const TurboHybrid::string& fileName);
		~FileParser() {
		}

		void LoadTransformData(TurboHybrid::Transform* transform, const json& data);
		void LoadRectData(TurboHybrid::RectangleRenderer* rect, const json& data);
		void LoadColliderData(TurboHybrid::RectangleCollider* collider, const json& data);
		void LoadPlayerControllerData(TurboHybrid::PlayerController* plr, const json& data);
		void LoadColorColliderData(TurboHybrid::ColliderColorChanger* cccr, const json& data);
		void LoadCubeRendererData(TurboHybrid::CubeRenderer* cube, const json& data);

		
		size_t GetNumOfGameObjects();

		void DeserializeGameobject(TurboHybrid::GameObject* gameObject, int index, TurboHybrid::ComponentSystem* allocator);

		bool hasComponent(const json& gameobject, const std::string& id);
		TurboHybrid::Vector3 ParseGameObjectPositionData(const json& gameObject);

		json GetGameObject(int id);
	private:
		TurboHybrid::string mFileName;
		json mData;

	};
}

