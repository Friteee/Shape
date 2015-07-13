#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "text.h"
#include "gui_element.h"
#include "../utility/configuration.h"
#include <string>
#include <memory>

namespace gui
{


/** \brief Text element
 *
 *  Just pure text
 */

class Text : public Gui_element
{
public:

    Text(utility::Configuration * config, std::string init_text , int x , int y, int init_text_size, SDL_Color init_color_key);
    ~Text();
    void         show() override;
    void         update() override;
    void         change_text(std::string init_text);
    void         handle_click(int x, int y)override;
    unsigned int get_length();

private:

    std::string                  text_;
    int                          text_size_;
    std::shared_ptr<TTF_Font *>  font_;
    SDL_Color                    color_key_;

};

}

#endif // TEXT_H_INCLUDED
