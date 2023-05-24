#ifndef __PHYSICSHELPER_H
#define __PHYSICSHELPER_H
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"

inline bool CircleVsCircleCollision(CircleCollider * c1, CircleCollider * c2) {
	return (c1->Position() - c2->Position()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool ColliderVsColliderCheck(Collider * c1, Collider * c2) {
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle) {
		return CircleVsCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	return false;
}
#endif