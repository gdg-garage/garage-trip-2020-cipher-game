#include "common.h"

#include <cage-core/image.h>
#include <cage-core/files.h>
#include <cage-core/math.h>
#include <cage-core/geometry.h>

namespace
{
	void renderHLine(Holder<Image> &img, const uint32 y)
	{
		const uint32 x1 = randomRange(1, 10);
		const uint32 x2 = x1 + 15 + randomRange(1, 10);
		for (uint32 x = x1; x <= x2; x++)
			img->set(x, y, vec3());
		if (randomChance() < 0.3)
			img->set(x1, y - 1, vec3());
		if (randomChance() < 0.6)
			img->set(x2, y + 1, vec3());
	}

	void renderVLine(Holder<Image> &img, const uint32 x)
	{
		const uint32 y1 = randomRange(1, 10);
		const uint32 y2 = y1 + 15 + randomRange(1, 10);
		for (uint32 y = y1; y <= y2; y++)
			img->set(x, y, vec3());
		if (randomChance() < 0.3)
			img->set(x - 1, y1, vec3());
		if (randomChance() < 0.6)
			img->set(x + 1, y2, vec3());
	}

	Holder<Image> makeLetter(const char c)
	{
		CAGE_ASSERT(c >= 'A' && c <= 'Z');
		Holder<Image> img = newImage();
		img->initialize(36, 36, 3);
		img->fill(vec3(1));
		const uint32 i = c - 'A';
		CAGE_ASSERT(i < 26);
		const uint32 xs = i % 5 + 1;
		const uint32 ys = i / 5 + 1;
		const uint32 hs = randomRange(4, 6);
		const uint32 vs = randomRange(4, 6);
		const uint32 ho = (7 - xs) * hs / 2;
		const uint32 vo = (7 - ys) * vs / 2;
		for (uint32 x = 0; x < xs; x++)
			renderVLine(img, x * hs + ho + randomRange(1, 3));
		for (uint32 y = 0; y < ys; y++)
			renderHLine(img, y * vs + vo + randomRange(1, 3));
		img->resize(45, 45);
		return img;
	}

	std::string str(const uint32 cypherIndex, const char c)
	{
		if (c >= 'A' && c <= 'Z')
		{
			static uint32 index = 0;
			index++;
			string n = stringizer() + cypherIndex + "/" + index + ".png";
			makeLetter(c)->exportFile(pathJoin(outputPath, n));
			return string(stringizer() + " <img src=\"" + cypherIndex + "/" + index + ".png\" /> ").c_str();
		}
		return std::string(&c, 1);
	}
}

void cipher3()
{
	constexpr uint32 cypherIndex = 3;

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toUpper(i);

	std::string s;
	for (const char c : i)
		s += str(cypherIndex, c);

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

