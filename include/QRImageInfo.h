#pragma once
#include <vector>
#include<map>
#include<utility>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <zxing/LuminanceSource.h>
#include <zxing/common/Counted.h>
#include <zxing/Reader.h>
#include <zxing/aztec/AztecReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/DecodeHints.h>
#include <zxing/datamatrix/DataMatrixReader.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/qrcode/decoder/BitMatrixParser.h>
#include <zxing/qrcode/ErrorCorrectionLevel.h>
#include <zxing/qrcode/Version.h>
#include <zxing/qrcode/decoder/DataBlock.h>
#include <zxing/qrcode/decoder/DecodedBitStreamParser.h>
#include <zxing/ReaderException.h>
#include <zxing/ChecksumException.h>
#include <zxing/common/reedsolomon/ReedSolomonException.h>
#include "MatSource.h"

#include "Version.h"
#include "Level.h"
#include "Mask.h"
#include "Pixel.h"
#include "CodeWord.h"
#include "Plan.h"


#include "MyDetector.h"
namespace info {
	class QRImageInfo {

	private:
		
		std::vector<std::vector<qrgen::Pixel>> modules;
		std::vector<qrgen::CodeWord> codewords;
		std::vector<int> blocks;
		std::vector<std::vector<int>>pixels;

		void invertCodeWord(int y, int x) { codewords[modules[y][x].getOffset() / 8].setTrue(); }

		int getBlockIndex(int y, int x) { return modules[y][x].getBlockIndex(); }

		bool getCodeWordStatus(int y, int x) { return codewords[modules[y][x].getOffset() / 8].getStatus(); }
	public:
		qrgen::Version *version;
		qrgen::LEVEL level;

		QRImageInfo() {};
		QRImageInfo(cv::Mat &image);

		~QRImageInfo(){
			modules.swap(std::vector<std::vector<qrgen::Pixel>>{});
			codewords.swap(std::vector<qrgen::CodeWord>{});
			blocks.swap(std::vector<int>{});
			pixels.swap(std::vector < std::vector<int>>{});
		}

		qrgen::Pixel::PixelRole getModuleRole(int y, int x) { return modules[y][x].getPixelRole();}
		
		int getBlock(int i) { return blocks[i]; }
		int getBlockSize() { return blocks.size(); }
		int getModuleSize() { return modules.size(); }
		std::pair<int,int> getPixel(int py, int px) {
			if (pixels[py][px] != -1)
				return std::make_pair(pixels[py][px] >> 16, pixels[py][px] & 0xFFFF);
			else
				return std::make_pair(-1, -1);
		}

		std::tuple<bool,int,int> tryModule(int y,int x){
			if (getCodeWordStatus(y, x))
				return std::make_tuple(false, getBlockIndex(y, x), getBlock(getBlockIndex(y, x)));
			else
				return std::make_tuple(true, getBlockIndex(y, x), getBlock(getBlockIndex(y, x))-1);
		}

		void invertModule(int y, int x) {
			modules[y][x].setPixel(qrgen::Pixel::INVERT.getPixel());
			if (!getCodeWordStatus(y, x)) {
				invertCodeWord(y, x);
				blocks[getBlockIndex(y, x)]--;
			}
		}
		



	};
}