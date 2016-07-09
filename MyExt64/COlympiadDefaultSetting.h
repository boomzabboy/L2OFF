
#pragma once

class COlympiadDefaultSetting {
public:
	static void Init();

	static const double Three;

	static int GetTransferingPointWrapper(COlympiadDefaultSetting *self, int a, int b, int c);
	static int GetPenaltyPointWrapper(COlympiadDefaultSetting *self, int a, int b);

	int GetTransferingPoint(int a, int b, int c);
	int GetPenaltyPoint(int a, int b);
};

