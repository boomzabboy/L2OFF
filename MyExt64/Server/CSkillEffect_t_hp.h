
#pragma once

class CSkillEffect_t_hp {
public:
	static void Init();
	static CSkillEffect_t_hp* Alloc(const size_t);

	static CSkillEffect_t_hp *last;

	bool Tick(class CObject *target, double d, unsigned int i);

	unsigned char padding0x0000[0x0018 - 0x0000];
	bool per;
};

