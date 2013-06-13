/*
 Copyright (C) Johan Ceuppens 2011

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include<fstream>
#include "RayMantaPolygonModel.h"
#include<cstdlib>
#include<cstring>

namespace ray3d {	

int PolygonModel::draw(Display **dpy, Window *w)
{

	for (PolygonVector::iterator vi = _polygons.begin(); vi != _polygons.end(); vi++ ) {
		(*vi).draw(dpy, w);
	}
	return 0;
}

int PolygonModel::filein(std::string const& filename)
{
	std::ifstream *ifs = new std::ifstream(filename.c_str());
	PointVector v;
	PointVector pv;
	Polygon poly;	
	for (; !ifs->eof(); ) {
		char *buf = new char[1024];//FIXME fixed size
		char *buf2 = new char[1024];//FIXME fixed size
		char *buf3 = new char[1024];//FIXME fixed size
		memset(buf,0,1024);
		memset(buf2,0,1024);
		memset(buf3,0,1024);
		(*ifs) >> buf;
		if (ifs->eof()) return -1; else (*ifs) >> buf2;
		if (ifs->eof()) return -1; else (*ifs) >> buf3;
		pv.push_back(Point(std::atof(buf),std::atof(buf2),std::atof(buf3)));
		v.push_back(Point(std::atof(buf),std::atof(buf2),std::atof(buf3)));
		poly += Point(std::atof(buf),std::atof(buf2),std::atof(buf3));
		
		/*for (PVec::iterator vi = v.begin(); vi != v.end(); vi++) {
			std::cout<< "*vi="<<(*vi).get_x()<<" buf="<< std::string(buf).c_str() <<std::endl;
			if ((*vi) == Point(std::atof(buf),std::atof(buf2),std::atof(buf3))) {
				_polygons.push_back(poly);
				poly = Polygon();
				v = PVec();
				pv = PVec();
			}
		}*/
		delete [] buf;
		delete [] buf2;
		delete [] buf3;
	}
	_polygons.push_back(poly);

	return 0;
}

int PolygonModel::fileout(std::string const& filename)
{
	char buf[1024];
	std::ofstream *ofs = new std::ofstream(filename.c_str());
	for (int i = 0; i < _polygons.size(); i++)
	for (int j = 0; j < _polygons[i].size(); j++) {
		sprintf(buf, "%e ", (double)(_polygons[i][j][0]));
		(*ofs) << buf; 
		sprintf(buf, "%e ", (double)(_polygons[i][j][1]));
		(*ofs) << buf; 
		sprintf(buf, "%e ", (double)(_polygons[i][j][2]));
		(*ofs) << buf; 
	}	
	return 0;
}

int PolygonModel::raytrace(Display **dpy, Window *w)
{ //FIXME
}

int PolygonModel::dithersunray(Display **dpy, Window *w)
{//FIXME
}

} // namespace ray3d

