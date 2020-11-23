#include "Dataset_Utils.h"


/* Reads the point cloud dataset and saves to a vector struct */
std::vector <data_utils::Point_Infos> data_utils::readPointsInfofromData()
{
	std::vector <data_utils::Point_Infos> pointsVector;


	float x, y, z, intensity, red, green, blue;

	static std::ifstream fileStream("C:\\Users\\dougv\\Desktop\\PointCViewer_Root\\External_Resources\\Dataset\\PointCloud-Input-EndCut.txt");
	
	//auto s = inputFile.peek() == std::ifstream::traits_type::eof();

	if (fileStream.is_open())
	{
		for (std::string line; std::getline(fileStream, line); )
		{
			fileStream >> x >> y >> z >> intensity >> red >> green >> blue;
			pointsVector.push_back(data_utils::Point_Infos{ x, y, z, intensity, red, green, blue });
		}
	}

	fileStream.close();

	return pointsVector;
}

/* Extracts the coordinates from each struct in the vector of structs */
std::vector <float> data_utils::getCoordinates(std::vector <data_utils::Point_Infos> pointsInfo)
{
	std::vector <float> coordinates;


	for (auto & pointsInfoStruct : pointsInfo)
	{
		coordinates.push_back(pointsInfoStruct.x);
		coordinates.push_back(pointsInfoStruct.y);
		coordinates.push_back(pointsInfoStruct.z);
	}

	return coordinates;
}

/* Extracts the RGB components from each struct in the vector of structs */
std::vector <float> data_utils::getPointsColor(std::vector <data_utils::Point_Infos> pointsInfo)
{
	std::vector <float> pointsColor;

	for (auto & pointsInfoStruct : pointsInfo)
	{
		pointsColor.push_back(pointsInfoStruct.red	  / 255.f);
		pointsColor.push_back(pointsInfoStruct.green  / 255.f);
		pointsColor.push_back(pointsInfoStruct.blue	  / 255.f);
	}

	return pointsColor;
}