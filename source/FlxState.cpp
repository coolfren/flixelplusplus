#include "flixel++/FlxState.hpp"

Flx::State::State()
{

}

void Flx::State::create(){
    
}

void Flx::State::update(){
    Flx::Group::update();
}

void Flx::State::draw(){
    Flx::Group::draw();
}

Flx::SubState::SubState(){

}

Flx::SubState::~SubState(){

}

void Flx::SubState::update(){
    
}

void Flx::SubState::draw(){
    
}