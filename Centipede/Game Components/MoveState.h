#ifndef _MoveState
#define _MoveState


struct OffsetArray;
class CentipedeHead;

class MoveState
{
public:
	MoveState() {};
	const OffsetArray* GetMoveOffsets() const { return MyMoveOffsets; }
	virtual const MoveState* GetNextState(CentipedeHead* chead) const = 0;
	virtual void Show() const = 0;

protected:
	const OffsetArray* MyMoveOffsets = nullptr;
};

#endif _MoveState