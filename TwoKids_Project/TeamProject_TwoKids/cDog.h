#pragma once
#include "cMonsterComponent.h"
class cDog :
	public cMonsterComponent
{
private:
	float fWaveElapsed;
	float fWaveDelay;

	int iAttackCount;
	int iNextWave;

	float fRad;
	float fRad_step;
public:
	cDog();
	virtual ~cDog();

	virtual void Start()					override;
	virtual void Update(float ElapsedTime)	override;

	void Attack(float ElapsedTime);

	void Wave01();
	void Wave02();

	void CreateBullet(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & dir, float speed);

	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) override;
};

