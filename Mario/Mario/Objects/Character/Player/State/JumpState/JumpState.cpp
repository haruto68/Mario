#include"JumpState.h"

#include"DxLib.h"
#include"../../../../../Utility/InputManager.h"
#include"../../Player.h"

JumpState::JumpState(class Player* p)
	: PlayerStateBase(p)
	, old_location(player->GetLocation())
	, up_acceleration(0.0f)
	, down_acceleration(0.0f)
{

}

JumpState::~JumpState()
{

}

void JumpState::Initialize()
{
	up_acceleration = -1.0f;
}

void JumpState::Finalize()
{

}

void JumpState::Update(float delta_seconds)
{
	// 入力機能インスタンス取得
	InputManager* input = InputManager::GetInstance();


	//加速度
	Vector2D velocity = 0.0f;
	up_acceleration += 0.01f;
	/*if (up_acceleration > 0.0f)
	{
		up_acceleration = 0.0f;
	}*/
	velocity.y += up_acceleration;


	////地面に触れたら
	//if (player->GetIsJump() == false)
	//{
	//	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	//	{
	//		//移動状態に遷移
	//		player->SetNextState(ePlayerState::RUN);
	//	}
	//	else
	//	{
	//		//停止状態に遷移
	//		player->SetNextState(ePlayerState::IDLE);
	//	}
	//}

	// 上昇加速度が0以上になったら
	if (up_acceleration >= 0.0f)
	{
		if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
		{
			//移動状態に遷移
			player->SetNextState(ePlayerState::RUN);
		}
		else
		{
			//停止状態に遷移
			player->SetNextState(ePlayerState::IDLE);
		}
	}



	//加速度セット
	player->SetVelocity(velocity);
	
}

void JumpState::Draw() const
{
	//
	DrawFormatString(100, 140, 0x000000, "JUMP");

	DrawFormatString(100, 300, 0x000000, "%.3f", up_acceleration);

	//座標情報を整数値に変換
	int x = 0, y = 0;
	x = (int)player->GetLocation().x;
	y = (int)player->GetLocation().y;

	//描画
	DrawBox(x - (int)(D_HARF), y - (int)(D_HARF), x + (int)(D_HARF), y + (int)(D_HARF), GetColor(255, 0, 0), FALSE);
}

ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}