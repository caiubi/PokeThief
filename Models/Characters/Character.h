enum CharacterType{};

class Character extends WorldObject{
	private:
		int state;
		double hpMax, hpCurrent;
		CharacterType type;

	protected:
		void changeState(int);
	public:
		Character(int, double, double, CharacterType);

		double getMaxHP();
		double getCurrentHP();

		void setCurrentHP(double);

		void getCharacterType();
}