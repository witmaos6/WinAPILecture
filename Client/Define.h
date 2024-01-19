#pragma once

#define SINGLE(type) public:\
					static type* GetInst()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					private:\
					type();\
					~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define CLONE(type) type* Clone(){return new type(*this);}

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define KEY_NONE(Key) KEY_CHECK(Key, KEY_STATE::NONE)
#define KEY_TAP(Key) KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_HOLD(Key) KEY_CHECK(Key, KEY_STATE::HOLD)
#define KEY_AWAY(Key) KEY_CHECK(Key, KEY_STATE::AWAY)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 64

enum class GROUP_TYPE
{
	DEFAULT,

	TILE,

	MONSTER,

	PLAYER,

	PROJ_PLAYER,

	PROJ_MONSTER,

	UI = 31,

	END = 32, // It means the end
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END, // It means the end
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,	
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,

	END
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,

	END
};
