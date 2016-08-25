class Pokeball: public WorldObject{
		private:
			bool opened;
		public:
			Pokeball(bool, WorldObject);
};

Pokeball::Pokeball(bool opened, WorldObject body) : WorldObject(body.getPosition(), body.getSize(), body.getTexture(), body.getSpeed()){
	this->opened = opened;
}