#pragma once
#include "Component_Common.h"

#include "headers/Util/Color.h"
#include "headers/Util/Rect.h"
#include "headers/Util/Vector3.h"

namespace TurboHybrid {
	class GameObject;
	class ComponentSystem;
	class bgfx::VertexBufferHandle;
	class bgfx::IndexBufferHandle;
	class bgfx::ProgramHandle;
	class CubeRenderer
	{
	public:

		CubeRenderer();
		~CubeRenderer();

		static enum { kCompID = 'CUBE' };
		static void CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);
		void load();
		void render(const float& deltatime);
		void SetBuffers(bgfx::VertexBufferHandle vbh,  bgfx::IndexBufferHandle ibh,  bgfx::ProgramHandle ph);

		bgfx::VertexBufferHandle GetVetexBuffer() { return m_vbh; };
		bgfx::IndexBufferHandle GetIndexBuffer() { return m_ibh; };
		bgfx::ProgramHandle GetProgramHandle() { return m_program; };

		

		TurboHybrid::GameObject* gameObject;
	protected:
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;

		bgfx::ProgramHandle m_program;
	};
}

