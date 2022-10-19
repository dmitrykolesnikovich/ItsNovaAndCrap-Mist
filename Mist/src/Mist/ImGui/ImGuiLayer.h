#pragma once

#include "Mist\Layer.h"

#include "Mist\Events\ApplicationEvent.h"
#include "Mist\Events\KeyEvent.h"
#include "Mist\Events\MouseEvent.h"

namespace Mist {

	class MIST_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
