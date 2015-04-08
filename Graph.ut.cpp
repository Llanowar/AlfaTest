#include "Graph.h"

#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MODULE GraphTestSuite

#include <boost/test/unit_test.hpp>

#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_of.hpp>

#include <ctime>

BOOST_AUTO_TEST_SUITE(GraphTestSuite)

void checkForValidSequence()
{
    AlfaTest::Graph graph;
    std::vector<std::string> dictionary;
    dictionary = boost::assign::list_of("asdfghj")("asddghj")("asddghd")("asds")("asddhhd")("bsddhhd")("bsddhho");

    std::vector<std::string> firstLastWords;
    firstLastWords = boost::assign::list_of("asdfghj")("bsddhho");

    for(size_t i(0); i < dictionary.size(); i++)
    {
        graph.addVertex(dictionary[i]);
    }

    graph.buildEdges();

    std::vector<std::string> path(graph.findShortestPath(firstLastWords[0], firstLastWords[1]));

	BOOST_CHECK_EQUAL(path.size(), 6);
	BOOST_CHECK_EQUAL(path[0], "asdfghj");
	BOOST_CHECK_EQUAL(path[1], "asddghj");
	BOOST_CHECK_EQUAL(path[2], "asddghd");
	BOOST_CHECK_EQUAL(path[3], "asddhhd");
	BOOST_CHECK_EQUAL(path[4], "bsddhhd");
	BOOST_CHECK_EQUAL(path[5], "bsddhho");
}

void checkForInvalidSequence()
{
    AlfaTest::Graph graph;
    std::vector<std::string> dictionary;
    dictionary = boost::assign::list_of("asdfghj")("asddghj")("asddghd")("asds")("asddhhd")("bsddhhd")("bsdZZho");

    std::vector<std::string> firstLastWords;
    firstLastWords = boost::assign::list_of("asdfghj")("bsdZZho");

    for(size_t i(0); i < dictionary.size(); i++)
    {
        graph.addVertex(dictionary[i]);
    }

    graph.buildEdges();

    std::vector<std::string> path(graph.findShortestPath(firstLastWords[0], firstLastWords[1]));

	BOOST_CHECK_EQUAL(path.size(), 0);
}

void checkForValidRandomSequence()
{
    std::srand(std::time(0));
    std::string originalWord = "AFDSLFHBBZXBCBJSDEBFEWUGFUYSAGEFDSADF";
    AlfaTest::Graph graph;
    std::vector<std::string> dictionary;
    dictionary.push_back(originalWord);
    for(size_t i(0); i < 1000; i++)
    {
        size_t n (std::rand() % originalWord.length());
        originalWord[n]++;
        dictionary.push_back(originalWord);
    }

    for(size_t i(0); i < dictionary.size(); i++)
    {
        graph.addVertex(dictionary[i]);
    }

    graph.buildEdges();

    std::vector<std::string> path(graph.findShortestPath(dictionary[0], dictionary[dictionary.size()-1]));

    // have solution
	BOOST_CHECK(path.size()>0 && path.size() <= dictionary.size());
}
 
BOOST_AUTO_TEST_CASE(GraphTest1)
{
    checkForValidSequence();
    checkForInvalidSequence();

    for (size_t i(0); i < 10; i++)
    {
        checkForValidRandomSequence();
    }
}

BOOST_AUTO_TEST_SUITE_END()
