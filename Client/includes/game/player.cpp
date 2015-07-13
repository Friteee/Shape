#include "player.h"

namespace game
{

void Player::notify(Object_command * command)
{
    command_mutex_.lock();
    bool finished = false;
    Object_command * iterator = newest_;
    // no commands found, create one
    if(iterator == nullptr)
    {
        newest_ = command;
        oldest_ = command;
        finished = true;
    }
    // append list of sorted commands
    while(!finished)
    {
        //if iterator's issue time is older than commands'
        if(iterator->get_time() < command->get_time())
        {
            //if iterator is the newest one
            if(iterator->get_next() == nullptr)
            {
                iterator->get_next() = command;
                command->get_previous() = iterator;
                if(iterator->get_previous() == nullptr)
                {
                    oldest_ = iterator;
                }
                finished = true;
            }
            //else if the iterator is not newest
            else
            {
                iterator->get_next()->get_previous() = command;
                command->get_next() = iterator->get_next();
                command->get_previous() = iterator;
                iterator->get_next() = command;
                if(iterator->get_previous() == nullptr)
                {
                    oldest_ = iterator;
                }
                finished = true;
            }
        }
        //move on
        else
        {
            // we hit the end of the queue
            if(iterator->get_previous() == nullptr)
            {
                iterator->get_previous() = command;
                command->get_next() = iterator;
                oldest_ = command;
                finished = true;
            }
            //move on
            else
            {
                iterator = iterator->get_previous();
            }
        }
    }

    command_mutex_.unlock();
}

void Player::update()
{
    command_mutex_.lock();

    Object_command * iterator = oldest_;
    while(iterator != nullptr)
    {
        iterator->execute(this);
        iterator = iterator->get_next();
    }
    command_mutex_.unlock();


}

Object_state * Player::get_state()
{
    return current_state_;
}

int Player::get_x()
{
    return x_;
}

int Player::get_y()
{
    return y_;
}

void Player::set_position(int set_x, int set_y)
{
    x_ = set_x;
    y_ = set_y;
}

}
