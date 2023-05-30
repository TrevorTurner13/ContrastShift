#include "ColourShifter.h"


ColourShifter::ColourShifter() {
	mIsWhite = false;
}

ColourShifter::~ColourShifter() {
	
}

bool ColourShifter::GetIsWhite() {
	return mIsWhite;
}

void ColourShifter::SetIsWhite(bool shift) {
	mIsWhite = shift;
}