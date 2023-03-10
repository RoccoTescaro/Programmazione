#pragma once
#include "Application.h"
#include <SFML/System.hpp>
#include "GameCharacter.h"

class Camera
{
public:
	Camera(const sf::Vector2<float>& viewPort);

	void update(const float& dt);

	void setTarget(const std::shared_ptr<GameCharacter>& target);

	inline void lock(bool condition) { locked = condition; };

	inline void lock() { locked = !locked; }; //toggle without parameters

	inline bool isLocked() { return locked; };

	inline void setCenter(const sf::Vector2<int>& center) { view.setCenter(center.x, center.y); };
	
	inline void setView(const sf::Vector2u& viewPort) { view.setSize(viewPort.x, viewPort.y); };

	inline const sf::View& getView() const { return view; };

private:
	sf::View view;
	const float viewZoomSpeed = Config::viewZoomSpeed;
	float viewMovementSpeed = Config::viewMovementSpeed; //movement speed not const couse changes accordingly with view dim.

	std::weak_ptr<GameCharacter> target;
	bool locked = false;

	const Input& input;
};