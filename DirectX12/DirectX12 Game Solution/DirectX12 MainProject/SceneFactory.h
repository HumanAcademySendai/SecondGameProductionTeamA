//
// SceneFactory.h
//

#include "TitleScene.h"
#include "MainScene.h"
#include "MainScene2.h"
#include "GameOverScene.h"
#include "ClearScene.h"


class SceneFactory final {
public:
	static std::unique_ptr<Scene> CreateScene(const NextScene nextScene)
	{
		std::unique_ptr<Scene> scene;
		switch (nextScene) {
		case NextScene::TitleScene:	    scene = std::make_unique<TitleScene>();	break;
		case NextScene::MainScene:	    scene = std::make_unique<MainScene>();	break;
		case NextScene::MainScene2:	    scene = std::make_unique<MainScene2>();	break;
		case NextScene::GameOverScene:	scene = std::make_unique<GameOverScene>();	break;
		case NextScene::ClearScene:	scene = std::make_unique<ClearScene>();	break;
		}
		return scene;
	}
};