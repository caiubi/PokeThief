class Team{
	private:
		Trainer trainer;
		Pokemon pokemon;

	public:
		Team(Trainer, Pokemon);
		void steal();
		void attack();

		void setAim();
};