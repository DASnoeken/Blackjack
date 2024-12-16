#ifndef CARD_HH
#define CARD_HH
class card
{
	public:
		card(int i)
		{
			value = i;
			ace = (value == 11);
		}

		bool getAce()
		{
			return ace;
		}

		int getValue()
		{
			return value;
		}
		
	private:
		int value;
		bool ace;
};
#endif
