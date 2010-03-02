#pragma once
#include "directx9.h"


using namespace D3D;

namespace MyCube
{
	enum Coords
	{
		R = 0,
		TETHA = 1,
		PHI = 2
	};

	class Cube
	{
	public:
		Cube();
		~Cube();
		Graphics device;
		HRESULT InitialObject();
		void Draw();
		void Move(float x, Coords alpha);
		unsigned CountIndex;
		unsigned CountVertex;
	private:
		float r, tetha, phi;
	};
}
