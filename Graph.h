#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <iostream>

namespace AlfaTest {
    class Graph {
        struct vertex_value_t {
            typedef boost::vertex_property_tag kind;
        };

        typedef boost::adjacency_list
        <
            boost::vecS,
            boost::vecS,
            boost::directedS,
            boost::property<vertex_value_t, std::string>,
            boost::property<boost::edge_weight_t, int>
        > BoostGraph;

        typedef boost::graph_traits<BoostGraph>::vertex_descriptor vertex_descriptor;
        typedef boost::graph_traits<BoostGraph>::vertex_iterator vertex_iterator;
        typedef boost::property_map<BoostGraph, vertex_value_t>::type vertex_property;


        static bool areBound(const std::string &lhs, const std::string &rhs) {
            size_t permutations(0);

            for (size_t i(0); i < rhs.length(); i++) {
                if (lhs[i] != rhs[i]) {
                    permutations++;
                }
            }

            return permutations <= 1;
        }

    public:

        Graph()
            : name_property(get(vertex_value_t(), g)) {
        }

        void addVertex(const std::string &vertex) {
            boost::add_vertex(vertex, g);
        }

        void buildEdges() {
            vertex_iterator vi, vi_end, next;
            boost::tie(vi, vi_end) = vertices(g);
            for (next = vi; vi != vi_end; vi = next) {
                ++next;
                vertex_iterator vi2, vi_end2, next2;
                boost::tie(vi2, vi_end2) = vertices(g);
                std::string vertexValue(boost::get(name_property, *vi));
                for (next2 = vi2; vi2 != vi_end2; vi2 = next2) {
                    ++next2;
                    if (areBound(vertexValue, boost::get(name_property, *vi2))) {
                        add_edge(*vi, *vi2, g);
                    }
                }

            }

        }

        std::vector <std::string> findShortestPath(const std::string &firstVertex, const std::string &lastVertex) {

            std::vector <vertex_descriptor> p(num_vertices(g));

            vertex_iterator firstVertexIterator;
            vertex_iterator lastVertexIterator;

            vertex_iterator vi, vi_end, next;
            boost::tie(vi, vi_end) = vertices(g);
            for (next = vi; vi != vi_end; vi = next) {
                ++next;
                std::string vertexValue(boost::get(name_property, *vi));

                if (vertexValue == firstVertex) firstVertexIterator = vi;
                if (vertexValue == lastVertex) lastVertexIterator = vi;
            }

            boost::dijkstra_shortest_paths
            (
                g,
                *lastVertexIterator,
                boost::predecessor_map
                (
                    boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))
                )
            );

#ifndef NDEBUG
            std::cout << "Parents:" << std::endl;
            vertex_iterator vi2, vend2;
            for (boost::tie(vi2, vend2) = vertices(g); vi2 != vend2; ++vi2) {
                std::cout << "the parent for [" << boost::get(name_property, *vi2) << " is [" <<
                boost::get(name_property, p[*vi2]) << "]" << std::endl;
            }
            std::cout << std::endl;
#endif

            std::vector <std::string> result;
            vertex_iterator current = firstVertexIterator;
            while (boost::get(name_property, *current) != lastVertex) {
                result.push_back(boost::get(name_property, *current));
                if (boost::get(name_property, *current) == boost::get(name_property, p[*current]))
                {
                    return std::vector<std::string>();
                }
                current = p[*current];
            }
            result.push_back(lastVertex);

            return result;
        }

    private:
        BoostGraph g;
        vertex_property name_property;
    };
}