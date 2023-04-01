class Item
{
public:
	CLASS("", "Item");

	MEMBER(UString*, name);
	MEMBER(UString*, text);
	MEMBER(unsigned long, skin);
	MEMBER(uint32_t, uid);
	MEMBER(ItemDefinition*, info);
	MEMBER(BaseProjectile*, heldEntity);
};