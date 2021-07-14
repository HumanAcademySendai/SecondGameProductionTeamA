//
// SceneFactory.h
//

#include "TitleScene.h"
#include"openingScene.h"
#include "MainScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"


class SceneFactory final {
public:
	static std::unique_ptr<Scene> CreateScene(const NextScene nextScene)
	{
		std::unique_ptr<Scene> scene;
		switch (nextScene) {
		case NextScene::TitleScene:	    scene = std::make_unique<TitleScene>();	break;
		case NextScene::openingScene:	    scene = std::make_unique<openingScene>();	break;
		case NextScene::MainScene:	    scene = std::make_unique<MainScene>();	break;
		case NextScene::GameOverScene:	scene = std::make_unique<GameOverScene>();	break;
		case NextScene::ClearScene:	scene = std::make_unique<ClearScene>();	break;
		}
		return scene;
	}
};