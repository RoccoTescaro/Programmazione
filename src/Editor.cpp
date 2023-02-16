#include "../hdr/Editor.h"
#include "../hdr/Config.h"

Editor::Editor() : cam()
{

    //BACKGROUND
    backgroundTexture.loadFromFile(Config::gameBackgroundTexturePath);
    background.setTexture(backgroundTexture);
    float backgroundScale = (float) window.getSize().x / backgroundTexture.getSize().x;
    background.setScale(backgroundScale, backgroundScale);
   
    //MOUSE
    mouseIndicator.setOutlineThickness(3);
	mouseIndicator.setSize(sf::Vector2<float>(map.getCellDim()));
	mouseIndicator.setFillColor(sf::Color(0, 0, 0, 0));
    window.setMouseCursorVisible(false);
    mouseFont.loadFromFile("../fnt/titleFont1.ttf");
	mousePosText.setFont(mouseFont);
	mousePosText.setCharacterSize(16);

    //VIEWS
    cam.lock(false);
    gui = cam.getView();
}

void Editor::update() 
{

	//MOUSE
	mouseGriddedPos = map.posFloatToInt(input.getMousePos(&cam.getView()));
	mouseIndicator.setPosition(map.posIntToFloat(mouseGriddedPos));
	mousePosText.setString(std::to_string(mouseGriddedPos.x) + ", " + std::to_string(mouseGriddedPos.y));
	mousePosText.setPosition(mouseIndicator.getPosition()+sf::Vector2<float>{map.getCellDim().x - mousePosText.getGlobalBounds().width, map.getCellDim().y - mousePosText.getGlobalBounds().height-4});

	//CAMERA
	cam.update();
    
	//BACKGROUND
	sf::Vector2<float> bgSize = cam.getView().getSize();
	sf::Vector2<float> bgPos = cam.getView().getCenter() - bgSize * 0.5f;
	background.setPosition(bgPos);
    float backgroundScale = (float) bgSize.x / backgroundTexture.getSize().x;
    background.setScale(backgroundScale, backgroundScale);
 
    //EDIT
    /*
    if(input.isKeyReleased(Input::Key::MouseL)){
        map.addGameCharacter(mouseGriddedPos,new Player(1,1,1,1,1));

    }
    */
}

void Editor::render() 
{
    window.setView(cam.getView());
    window.draw(background);
    map.render(window);
    window.draw(mouseIndicator);
    window.draw(mousePosText);
    window.setView(gui);
}

