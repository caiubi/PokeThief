class Pokeball extends WorldObject{
		private:
			bool opened;
			double speedVector[2];
		public:
			Pokeball(bool, double speedVector[2]);
};