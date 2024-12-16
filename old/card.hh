#ifndef CARD_HH
#define CARD_HH
class card{
	public:
		card(int i)
		{
			value = i;
		}

		int getValue()
		{
			return value;
		}
		
	private:
		int value;
};
#endif
