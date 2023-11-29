#include "Shape.h"


Shape::Shape(const size_t verticiesCapacity, const size_t indiciesCapacity)
    : VO_{ verticiesCapacity, indiciesCapacity }
{   }


Shape::Shape(const char* vertexShader, const char* fragmentShader)
    : SO_{ vertexShader, fragmentShader }
{   }


Shape::Shape(const size_t verticiesCapacity, const size_t indiciesCapacity,
    const char* vertexShader, const char* fragmentShader)
    : VO_{ verticiesCapacity, indiciesCapacity }
    , SO_{ vertexShader, fragmentShader }
{   }


Shape::~Shape()
{
    delete lightData_;
}