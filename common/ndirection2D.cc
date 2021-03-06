/****************************************************************************
 **
 **  Copyright (C) 2015 Andreas Mussgiller
 **
 **  This program is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  This program is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 **
 ****************************************************************************/

#include <cmath>

#include "npoint2D.h"
#include "ndirection2D.h"

NDirection2D::NDirection2D()
: NVector2D(0., 1.)
{

}

NDirection2D::NDirection2D(double x, double y)
: NVector2D(x, y)
{
  normalize();
}

NDirection2D::NDirection2D(const NPoint2D& a, const NPoint2D& b)
: NVector2D(a, b)
{
  normalize();
}

NDirection2D::NDirection2D(const NVector2D& other)
: NVector2D(other)
{
  normalize();
}

NDirection2D::~NDirection2D()
{

}

void NDirection2D::normalize()
{
  double l = length();
  x_ /= l;
  y_ /= l;
}
