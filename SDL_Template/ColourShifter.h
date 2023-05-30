#ifndef __COLOURSHIFTER_H
#define __COLOURSHIFTER_H

class ColourShifter {
private:

	bool mIsWhite;
	
public:
	ColourShifter();
	~ColourShifter();

	bool GetIsWhite();
	void SetIsWhite(bool shift);
};

#endif 