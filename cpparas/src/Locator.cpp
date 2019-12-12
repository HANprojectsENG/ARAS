#include "Locator.hpp"

Locator::Locator(std::shared_ptr<StateMachine> stateMachine_, std::shared_ptr<ImageLoader> imageLoader_)
    : stateMachine(stateMachine_)
    , imageLoader(imageLoader_)
{
}
