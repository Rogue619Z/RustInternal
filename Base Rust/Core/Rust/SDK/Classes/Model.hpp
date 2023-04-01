class Model
{
public:
	CLASS("", "Model");

	MEMBER(Transform*, rootBone);
	MEMBER(Transform*, headBone);
	MEMBER(Transform*, eyeBone);
	MEMBER(Array<Transform*>*, boneTransforms);
};