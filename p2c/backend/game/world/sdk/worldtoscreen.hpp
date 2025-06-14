#pragma once
#ifndef W2S
#define W2S

#include "../../../driver/driver.hpp"
#include "../../../framework/d3d/d3dx9math.h"

#define M_PI 3.14159265358979323846264338327950288419716939937510

class Vector3
{
public:
	double x, y, z;

	Vector3()
	{
		x = y = z = 0.0f;
	}

	Vector3(double X, double Y, double Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector3(double XYZ)
	{
		x = XYZ; y = XYZ; z = XYZ;
	}

	Vector3(double* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector3(const double* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	__forceinline Vector3& operator=(const Vector3& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	__forceinline Vector3& operator=(const double* v)
	{
		x = v[0]; y = v[1]; z = v[2]; return *this;
	}

	__forceinline double& operator[](int i)
	{
		return ((double*)this)[i];
	}

	__forceinline double operator[](int i) const
	{
		return ((double*)this)[i];
	}

	__forceinline Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	__forceinline Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	__forceinline Vector3& operator*=(const Vector3& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	__forceinline Vector3& operator/=(const Vector3& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	__forceinline Vector3& operator+=(double v)
	{
		x += v; y += v; z += v; return *this;
	}

	__forceinline Vector3& operator-=(double v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	__forceinline Vector3& operator*=(double v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	__forceinline Vector3& operator/=(double v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	__forceinline Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	__forceinline Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	__forceinline Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	__forceinline Vector3 operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	__forceinline Vector3 operator/(const Vector3& v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	__forceinline Vector3 operator+(double v) const
	{
		return Vector3(x + v, y + v, z + v);
	}

	__forceinline Vector3 operator-(double v) const
	{
		return Vector3(x - v, y - v, z - v);
	}

	__forceinline Vector3 operator*(double v) const
	{
		return Vector3(x * v, y * v, z * v);
	}

	__forceinline Vector3 operator/(double v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	__forceinline double Distance(Vector3 v)
	{
		return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z));
	}

	__forceinline double Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	__forceinline double Dot(const Vector3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}
};

typedef struct entitys
{
	uintptr_t actor;
	uintptr_t mesh;
	uintptr_t currentweapon;
	uintptr_t playerstate;
}entitys;

std::vector<entitys> entitylist;

struct unrealengine
{
	struct FQ
	{
		double x;
		double y;
		double z;
		double w;
	};

	FQ rotation;
	Vector3 translation;
	Vector3 scale;

	__forceinline __forceinline auto visibilitycheck(DWORD_PTR mesh) -> bool
	{
		return 0;
	}

	__forceinline auto matrixtos() -> D3DXMATRIX
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		double x2 = rotation.x + rotation.x;
		double y2 = rotation.y + rotation.y;
		double z2 = rotation.z + rotation.z;

		double xx2 = rotation.x * x2;
		double yy2 = rotation.y * y2;
		double zz2 = rotation.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		double yz2 = rotation.y * z2;
		double wx2 = rotation.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;
		double xy2 = rotation.x * y2;
		double wz2 = rotation.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		double xz2 = rotation.x * z2;
		double wy2 = rotation.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}

	__forceinline auto matrix(Vector3 rotation, Vector3 origin = Vector3(0, 0, 0)) -> D3DXMATRIX
	{
		float radPitch = (rotation.x * float(M_PI) / 180.f);
		float radYaw = (rotation.y * float(M_PI) / 180.f);
		float radRoll = (rotation.z * float(M_PI) / 180.f);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	__forceinline auto matrixm(D3DMATRIX pM1, D3DMATRIX pM2) -> D3DXMATRIX
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}

	__forceinline auto bonewithrotation(uintptr_t MESH, int ID) -> Vector3
	{
		uintptr_t BoneA = ioctl->read<uintptr_t>(MESH + offsets->bonearray);
		if (BoneA == NULL)
		{
			BoneA = ioctl->read<uintptr_t>(MESH + offsets->bonearray + 0x10);
		}
		unrealengine Bone = ioctl->read<unrealengine>(BoneA + (ID * offsets->bonec));
		unrealengine Comp = ioctl->read<unrealengine>(MESH + offsets->comptowrld);
		D3DMATRIX matrix = matrixm(Bone.matrixtos(), Comp.matrixtos());
		return Vector3(matrix._41, matrix._42, matrix._43);
	}

	struct cdecrypt
	{
		Vector3 location;
		Vector3 rotation;
		float fov;
	};

	__forceinline auto viewpoint() -> cdecrypt
	{
		uintptr_t cachedgworld = ioctl->read<uintptr_t>(globals->imagebase + offsets->gworld);
		uintptr_t cachedgameinstance = ioctl->read<uintptr_t>(cachedgworld + offsets->gameinstance);
		uintptr_t cachedlocalplayers = ioctl->read<uintptr_t>(cachedgameinstance + offsets->localplayers);
		uintptr_t cachedplayercontroller = ioctl->read<uintptr_t>(cachedlocalplayers + offsets->playercontroller);

		cdecrypt camera;

		auto locationp = ioctl->read<uintptr_t>(cachedgworld + 0x110);
		auto rotationp = ioctl->read<uintptr_t>(cachedgworld + 0x120);

		struct fnrotation
		{
			double a;
			double b;
			double c;
		}fnrotation;

		fnrotation.a = ioctl->read<double>(rotationp);
		fnrotation.b = ioctl->read<double>(rotationp + 0x20);
		fnrotation.c = ioctl->read<double>(rotationp + 0x1d0);

		camera.location = ioctl->read<Vector3>(locationp);
		camera.rotation.x = asin(fnrotation.c) * (180.0 / M_PI);
		camera.rotation.y = ((atan2(fnrotation.a * -1, fnrotation.b) * (180.0 / M_PI)) * -1) * -1;
		camera.fov = ioctl->read<float>((uintptr_t)cachedplayercontroller + 0x394) * 90.f;

		return camera;
	}

	__forceinline auto worldtscreen(Vector3 WorldLocation) -> Vector3
	{
		cdecrypt ViewPoint = viewpoint();
		D3DMATRIX MatrixT = matrix(ViewPoint.rotation);
		Vector3 AxisX = Vector3(MatrixT.m[0][0], MatrixT.m[0][1], MatrixT.m[0][2]);
		Vector3 AxisY = Vector3(MatrixT.m[1][0], MatrixT.m[1][1], MatrixT.m[1][2]);
		Vector3 AxisZ = Vector3(MatrixT.m[2][0], MatrixT.m[2][1], MatrixT.m[2][2]);
		Vector3 Delta = WorldLocation - ViewPoint.location;
		Vector3 Transformed = Vector3(Delta.Dot(AxisY), Delta.Dot(AxisZ), Delta.Dot(AxisX));
		if (Transformed.z < 1.f)
		{
			Transformed.z = 1.f;
		}
		return Vector3((globals->width / 2.0f) + Transformed.x * (((globals->width / 2.0f) / tanf(ViewPoint.fov * (float)M_PI / 360.f))) / Transformed.z, (globals->height / 2.0f) - Transformed.y * (((globals->width / 2.0f) / tanf(ViewPoint.fov * (float)M_PI / 360.f))) / Transformed.z, 0);
	}

	__forceinline auto vecvalid(Vector3 vec3) -> bool
	{
		return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
	}

	__forceinline auto cdistance(double x1, double y1, double x2, double y2) -> double
	{
		return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	}
};

std::unique_ptr<unrealengine> uengine = std::make_unique<unrealengine>();

#endif