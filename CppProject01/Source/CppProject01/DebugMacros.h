#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if (GetWorld()) { \
	DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true); };

#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) { \
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true); };

#define DRAW_POINT(Location) if (GetWorld()) { \
	DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true); };

#define DRAW_VECTOR(StartLocation, EndLocation) if (GetWorld()) { \
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true); \
	DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, true); };

