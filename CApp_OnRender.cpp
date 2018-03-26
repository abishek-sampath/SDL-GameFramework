#include "CApp.h"

void CApp::OnRender()
{
    GArea::AreaControl.OnRender(-GCamera::CameraControl.GetX(),
                                -GCamera::CameraControl.GetY());

    for(unsigned int i=0; i < GEntity::EntityList.size(); i++) {
        if(!GEntity::EntityList[i])
            continue;
        GEntity::EntityList[i]->OnRender(true);
    }


    // render score
    FontTexture scoreTexture;
    FontTexture timeTexture;
    std::stringstream scoreText;
    scoreText.str("");
    scoreText << "SCORE : " << score;
    if (scoreTexture.loadFromRenderedText(renderer, scoreText.str().c_str(), whiteColor, font, SCREEN_WIDTH))
    {
        scoreTexture.render(renderer, (SCREEN_WIDTH - scoreTexture.getWidth() - 10), 20);
    }
    // render time passed
    if(timeText.str().size() > 0 && timeTexture.loadFromRenderedText(renderer, timeText.str().c_str(), whiteColor, font, 50))
    {
        timeTexture.render(renderer, ((SCREEN_WIDTH / 2) - (timeTexture.getWidth() / 2)), 20);
    }



    SDL_RenderPresent(renderer);
}


//TextureUtils::OnDraw(ANIM_2, renderer, resourceManager,
//           290, 220,100, 50,
//           Anim.GetCurrentFrame()*75, 0, 75, 132);
