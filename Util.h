#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <fstream>
#include <iostream>

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>


namespace util {


inline
std::vector<QVector3D> genTriangle() {
	std::vector<QVector3D> data;
    data.reserve(12);
    /*data.emplace_back(QVector3D(-1.0, -2.0/3.0, 0.0));
    data.emplace_back(QVector3D(-2.0, -1.0, 0.0));
    data.emplace_back(QVector3D(-1.0, 2.0/3.0, 0.0));
    data.emplace_back(QVector3D(-2.0, 1.0, 0.0));
    data.emplace_back(QVector3D(1, -2.0/3.0, 0.0));
    data.emplace_back(QVector3D(+1.0, -1.0, 1.0));

    data.emplace_back(QVector3D(1.0, 2.0/3.0, 0.0));
    data.emplace_back(QVector3D(1.0, 1.0, 0.0));
    data.emplace_back(QVector3D(1.0, -2.0/3.0, 0.0));
    data.emplace_back(QVector3D(+1.0, -1.0, 1.0));
    data.emplace_back(QVector3D(-1, 2.0/3.0, 0.0));
    data.emplace_back(QVector3D(-2.0, +1.0, 0.0));*/

    data.emplace_back(QVector3D(-1.0, -1.0, 0.0));
    data.emplace_back(QVector3D(-2.0, -1.0, 0.0));
    data.emplace_back(QVector3D(-1.0, 1.0, 0.0));
    data.emplace_back(QVector3D(-2.0, 1.0, 0.0));
    data.emplace_back(QVector3D(1, -1.0, 0.0));
    data.emplace_back(QVector3D(+1.0, -1.0, 1.0));

    data.emplace_back(QVector3D(1.0, 1.0, 0.0));
    data.emplace_back(QVector3D(1.0, 1.0, 0.0));
    data.emplace_back(QVector3D(1.0, -1.0, 0.0));
    data.emplace_back(QVector3D(+1.0, -1.0, 1.0));
    data.emplace_back(QVector3D(-1, 1.0, 0.0));
    data.emplace_back(QVector3D(-2.0, +1.0, 0.0));
	std::cout << "num vertices: " << data.size() << std::endl;
	return data;
}


} // namespace util

#endif
