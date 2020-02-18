/*
 * Geometry.hpp
 *
 *  Created on: 18 lut 2020
 *      Author: kamil
 */

#ifndef SRC_UNGAME_GEOMETRY_HPP_
#define SRC_UNGAME_GEOMETRY_HPP_

const float f360 = 360.0, f180 = 180.0;
/**
 *  \brief  The structure that defines a point (double)
 */
// Converts degrees to radians.
#define degToRad(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radToDeg(angleRadians) (angleRadians * 180.0 / M_PI)

#endif /* SRC_UNGAME_GEOMETRY_HPP_ */
