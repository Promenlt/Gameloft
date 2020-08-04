#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	m_position = Vector3(0.0f, 0.0f, 3.0f);
	m_target = Vector3(0.0f, 0.0f, 0.0f);
	m_up = Vector3(0.0f, 1.0f, 0.0f);

	m_projectionMatrix.SetPerspective(1.0f, Globals::screenWidth / Globals::screenHeight, 0.1f, 100.0f);

	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	m_viewMatrix.m[0][0] = xaxis.x;
	m_viewMatrix.m[0][1] = yaxis.x;
	m_viewMatrix.m[0][2] = zaxis.x;
	m_viewMatrix.m[0][3] = 0;

	m_viewMatrix.m[1][0] = xaxis.y;
	m_viewMatrix.m[1][1] = yaxis.y;
	m_viewMatrix.m[1][2] = zaxis.y;
	m_viewMatrix.m[1][3] = 0;

	m_viewMatrix.m[2][0] = xaxis.z;
	m_viewMatrix.m[2][1] = yaxis.z;
	m_viewMatrix.m[2][2] = zaxis.z;
	m_viewMatrix.m[2][3] = 0;

	m_viewMatrix.m[3][0] = -m_position.Dot(xaxis);
	m_viewMatrix.m[3][1] = -m_position.Dot(yaxis);
	m_viewMatrix.m[3][2] = -m_position.Dot(zaxis);
	m_viewMatrix.m[3][3] = 1;
}

Camera::~Camera()
{
}

void Camera::CalculateViewMatrix()
{
	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	m_viewMatrix.m[0][0] = xaxis.x;
	m_viewMatrix.m[0][1] = yaxis.x;
	m_viewMatrix.m[0][2] = zaxis.x;
	m_viewMatrix.m[0][3] = 0;

	m_viewMatrix.m[1][0] = xaxis.y;
	m_viewMatrix.m[1][1] = yaxis.y;
	m_viewMatrix.m[1][2] = zaxis.y;
	m_viewMatrix.m[1][3] = 0;

	m_viewMatrix.m[2][0] = xaxis.z;
	m_viewMatrix.m[2][1] = yaxis.z;
	m_viewMatrix.m[2][2] = zaxis.z;
	m_viewMatrix.m[2][3] = 0;

	m_viewMatrix.m[3][0] = -m_position.Dot(xaxis);
	m_viewMatrix.m[3][1] = -m_position.Dot(yaxis);
	m_viewMatrix.m[3][2] = -m_position.Dot(zaxis);
	m_viewMatrix.m[3][3] = 1;
}

void Camera::CalculateWorldMatrix()
{
	zaxis = (m_position - m_target).Normalize();
	xaxis = (m_up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	m_viewMatrix.m[0][0] = xaxis.x;
	m_viewMatrix.m[0][1] = xaxis.y;
	m_viewMatrix.m[0][2] = xaxis.z;
	m_viewMatrix.m[0][3] = 0;

	m_viewMatrix.m[1][0] = yaxis.x;
	m_viewMatrix.m[1][1] = yaxis.y;
	m_viewMatrix.m[1][2] = yaxis.z;
	m_viewMatrix.m[1][3] = 0;

	m_viewMatrix.m[2][0] = zaxis.x;
	m_viewMatrix.m[2][1] = zaxis.y;
	m_viewMatrix.m[2][2] = zaxis.z;
	m_viewMatrix.m[2][3] = 0;

	m_viewMatrix.m[3][0] = m_position.x;
	m_viewMatrix.m[3][1] = m_position.y;
	m_viewMatrix.m[3][2] = m_position.z;
	m_viewMatrix.m[3][3] = 1;
}

void Camera::MoveForward(float deltaTime)
{
	Vector3 deltaMove = -(m_position - m_target).Normalize()*deltaTime;
	UpdateCamera(deltaMove);
}

void Camera::MoveBackward(float deltaTime)
{
	Vector3 deltaMove = (m_position - m_target).Normalize()*deltaTime;
	UpdateCamera(deltaMove);
}

void Camera::MoveLeft(float deltaTime)
{
	Vector3 deltaMove = -xaxis.Normalize()*deltaTime;
	UpdateCamera(deltaMove);
}

void Camera::MoveRight(float deltaTime)
{
	Vector3 deltaMove = xaxis.Normalize()*deltaTime;
	UpdateCamera(deltaMove);
}
void Camera::RotateLeft(float deltaTime)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_position - m_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * RotationMatrixAroundY(-deltaTime);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotateRight(float deltaTime)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_position - m_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * RotationMatrixAroundY(deltaTime);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotateUp(float deltaTime) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_position - m_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * RotationMatrixAroundX(-deltaTime);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
void Camera::RotateDown(float deltaTime) {
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(m_position - m_target).Length(), 1.0f);
	Vector4 localNewTarget = localTarget * RotationMatrixAroundX(deltaTime);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}
Matrix Camera::RotationMatrixAroundY(float angle) {
	Matrix rotation;
	Vector4 RotateAxis = Vector4(yaxis,0.0f);
	RotateAxis = RotateAxis*GetViewMatrix();
	return rotation.SetRotationAngleAxis(angle, RotateAxis.x, RotateAxis.y, RotateAxis.z);
}
Matrix Camera::RotationMatrixAroundX(float angle) {
	Matrix rotation;
	Vector4 RotateAxis = Vector4(xaxis, 0.0f);
	RotateAxis = RotateAxis*GetViewMatrix();
	return rotation.SetRotationAngleAxis(angle, RotateAxis.x, RotateAxis.y, RotateAxis.z);
}
void Camera::CheckKeyPress(unsigned char key, bool isPressed)
{
	switch (key)
	{
	case 'W':
		if (isPressed)
		{
			m_direction = MOVE_FORWARD;
		}
		break;
	case 'S':
		if (isPressed)
		{
			m_direction = MOVE_BACKWARD;
		}
		break;
	case 'A':
		if (isPressed)
		{
			m_direction = MOVE_LEFT;
		}
		break;
	case 'D':
		if (isPressed)
		{
			m_direction = MOVE_RIGHT;
		}
		break;
	case 'J':
		if (isPressed)
		{
			m_direction = ROTATION_LEFT;
		}
		break;
	case 'L':
		if (isPressed)
		{
			m_direction = ROTATION_RIGHT;
		}
		break;
	case 'I':
		if (isPressed)
		{
			m_direction = ROTATION_UP;
		}
		break;
	case 'K':
		if (isPressed)
		{
			m_direction = ROTATION_DOWN;
		}
		break;
	default:
		m_direction = 0;
		break;
	}
}

void Camera::Update(float deltaTime)
{
	switch (m_direction)
	{
	case MOVE_FORWARD:
		MoveForward(deltaTime);
		break;
	case MOVE_BACKWARD:
		MoveBackward(deltaTime);
		break;
	case MOVE_LEFT:
		MoveLeft(deltaTime);
		break;
	case MOVE_RIGHT:
		MoveRight(deltaTime);
		break;
	case ROTATION_LEFT:
		RotateLeft(deltaTime);
		break;
	case ROTATION_RIGHT:
		RotateRight(deltaTime);
		break;
	case ROTATION_UP:
		RotateUp(deltaTime);
		break;
	case ROTATION_DOWN:
		RotateDown(deltaTime);
		break;
	default:
		break;
	}
	m_direction = 0;
}


void Camera::UpdateCamera(Vector3 deltaMove)
{
	m_position += deltaMove;
	m_target += deltaMove;
}
Matrix Camera::GetWorldMatrix()
{
	this->CalculateWorldMatrix();
	return this->m_worldMatrix;
}
Matrix Camera::GetViewMatrix()
{
	this->CalculateViewMatrix();
	return this->m_viewMatrix;
}

Matrix Camera::GetProjectionMatrix()
{
	return this->m_projectionMatrix;
}
