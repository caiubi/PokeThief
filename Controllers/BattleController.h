class BattleController: public Controller{
	private:
		Team *teamLeft, *teamRight;
		Scenario *scenario;
		bool turn;
	public:
		BattleController(Bounds, Bounds);

		void start();

		void processKeyboardInput();
		void processMouseInput();

		void drawMembersAndUpdate(double, GLFWwindow*);

};

BattleController::BattleController(Bounds screenBounds, Bounds spaceBounds) : Controller(0){
	turn = true;
    scenario = new Scenario(GRASS, screenBounds, spaceBounds);
    Point p = scenario->getFloorHeightAt(2*(screenBounds.right/3));
    p.y += (0.240241/2.0)+0.05;

    WorldObject corpo = WorldObject(p, (Dimension){0.2222,0.240241}, "ImageResources/trainer.png", (Vector2D){0,0});
    Trainer *trainer = new Trainer(2, corpo);

    teamLeft = new Team(trainer, NULL);
}

void BattleController::drawMembersAndUpdate(double deltaT, GLFWwindow* window){
    scenario->draw();
	teamLeft->drawMembers(deltaT);
//	teamRight->drawMembers(deltaT);
}
