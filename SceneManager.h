#pragma once

//ÉVÅ[Éì
static enum Scene
{
	Title,
	NewGame,
	GamePlay,
	NewClear,
};

class SceneManager
{
private:
	SceneManager();
	~SceneManager();
public:
	static SceneManager* GetInstance();
	void ChangeScene(Scene nextScene);
	Scene GetScene() { return scene_; };
	void SetScene(Scene scene) { scene_ = scene; };
private:
	Scene scene_;
};

