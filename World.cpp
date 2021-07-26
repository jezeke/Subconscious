#pragma once
#include <fstream>
#include <iterator>
#include <algorithm>
#include <json.hpp>
#include <stdint.h>
#include "SubSystems.cpp"

class World
{
  private:

  public:
    uint32_t sizeX;
    uint32_t sizeY;
    uint32_t sizeZ;

    std::vector<std::vector<std::vector<bool>>> data; //access as vector[x][y][z]
    //std::vector<std::vector<std::vector<uint8_t>>> data; //access as vector[x][y][z]


    //constructor
    World()
    {
      std::ifstream fs;
      /*fs.open("assets/world1.json", std::fstream::in);
      std::string jsonFile << fs;
      fs.close();

      nlohmann::json js = nlohmann::json::parse(jsonFile);*/

      //extract settings & info from world json

      fs.open("assets/monk1.rawvox", std::ios::in | std::ios::binary);

      //load header fields
      std::vector<uint32_t> header(5); //space for all 5 32bit header values
      fs.read(reinterpret_cast<char*>(&header[0]), header.size() * sizeof(uint32_t));

      if(header[0] != 1381388120) throw std::invalid_argument("invalid file header"); //RVOX magic header

      sizeX = header[1];
      sizeZ = header[2];
      sizeY = header[3];

      data.resize(sizeX, std::vector<std::vector<bool>>(sizeY, std::vector<bool>(sizeZ)));
      std::vector<uint8_t> buffer(sizeX*sizeY*sizeZ);

      //if memory usage here is a problem, rework below loops to operate on stream, rather than in-memory.
      fs.read(reinterpret_cast<char*>(&buffer[0]), buffer.size() * sizeof(uint8_t));

      auto iter = begin(buffer);
      for(uint32_t y = sizeY; y-- > 0; )
      {
        for(uint32_t z = sizeZ; z-- > 0; )
        {
          for(uint32_t x = sizeX; x-- > 0; )
          {
            if(iter == end(buffer))
            {
              throw std::invalid_argument("not enough file data; invalid lengths");
            }

            //data[x][y][z] = *iter;
            data[x][y][z] = *iter >= UINT8_MAX/2;
            iter++;
          }
        }
      }

      if(iter != end(buffer))
      {
        throw std::invalid_argument("file data remaining; invalid lengths");
      }

      fs.close();
    }

    void simulate(float fElapsedTime, SubSystems sub)
    {
      //check SubSystems engine state and update sub position accordingly
    }
};
