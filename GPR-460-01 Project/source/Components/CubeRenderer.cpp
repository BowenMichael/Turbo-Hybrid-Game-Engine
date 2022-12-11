#pragma once
#include "headers/Components/CubeRenderer.h"
#include <headers/Components/Component_System.h>
#include <headers/GameObject.h>
#include <bgfx/include/bgfx/platform.h>
#include "bgfx/include/bgfx/bgfx.h"
// math
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

TurboHybrid::CubeRenderer::CubeRenderer() :
	m_vbh(),
	m_ibh(),
	m_program(),
	gameObject(nullptr)
{

}

TurboHybrid::CubeRenderer::~CubeRenderer()
{
}

void TurboHybrid::CubeRenderer::CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator)
{
	CubeRenderer* tmp = allocator->allocateCubeRenderer();
	tmp->gameObject = gm;
	gm->SetCubeRenderer(tmp);
}

void TurboHybrid::CubeRenderer::load()
{
}

void TurboHybrid::CubeRenderer::render(const float& deltatime)
{
	assert(m_vbh.idx != 0 || m_ibh.idx != 0 || m_program.idx != 0);
	//set up render state for object
	uint64_t state = 0
		| (BGFX_STATE_WRITE_R)
		| (BGFX_STATE_WRITE_G)
		| (BGFX_STATE_WRITE_B)
		| (BGFX_STATE_WRITE_A)
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CW
		| BGFX_STATE_MSAA
		| UINT64_C(0)
		;

	// set model matrix for the cube's individual location, rotation and scale
	glm::mat4x4 model = glm::mat4(1.0f); // init with no translation
	Vector3 pos3 = gameObject->GetTransform()->GetLocation();
	glm::vec3 pos = glm::vec3(pos3.x, pos3.y, pos3.z);
	model = glm::translate(model, pos);
	float rotationDirection = 100.0f;
	if (gameObject->GetPlayerController() != nullptr) {
		rotationDirection *= -1;
	}
	model = glm::rotate(model, deltatime / rotationDirection, glm::vec3(1.0f, 1.0f, 0.0f));// (model, glm::vec3(0.0, -5.0f, 0.0f));
	//glm::rotate(model, 3.14f, glm::vec3(1.0));        // perform a rotation about the axis (1,1,1) (currently does not work)
	bgfx::setTransform(&model);

	// load shader programs
	bgfx::setVertexBuffer(0, m_vbh); //Vertex buffer could be shared on a per object basis to be consistent with the array of components system
	bgfx::setIndexBuffer(m_ibh);

	// Set render states.
	bgfx::setState(state);

	bgfx::submit(0, m_program);
}

void TurboHybrid::CubeRenderer::SetBuffers( bgfx::VertexBufferHandle vbh,  bgfx::IndexBufferHandle ibh,  bgfx::ProgramHandle ph)
{
	m_vbh = vbh;
	m_ibh = ibh;
	m_program = ph;

}
