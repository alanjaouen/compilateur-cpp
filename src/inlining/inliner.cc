/**
 ** \file inlining/inliner.cc
 ** \brief Implementation of inlining::Inliner.
 */

#include <boost/graph/transitive_closure.hpp>

#include <inlining/inliner.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>
#include <callgraph/libcallgraph.hh>

namespace inlining
{
  using namespace ast;

  Inliner::Inliner(const ast::Ast& tree)
    : super_type(), rec_funs_()
  {
    // Compute the transitive closure of the call graph to compute the
    // set of recursive functions.
    const callgraph::CallGraph* graph = callgraph::callgraph_compute(tree);
    callgraph::CallGraph closure;
    boost::transitive_closure(*graph, closure);

    callgraph::callgraph_vertex_iter_type i;
    callgraph::callgraph_vertex_iter_type i_end;
    // Re-attach properties to the vertices.
    for (std::tie(i, i_end) = boost::vertices(closure); i != i_end; ++i)
      closure[*i] = (*graph)[*i];
    // Detect recursive functions.
    for (std::tie(i, i_end) = boost::vertices(closure); i != i_end; ++i)
      {
        callgraph::callgraph_neighb_iter_type j;
        callgraph::callgraph_neighb_iter_type j_end;
        for (std::tie(j, j_end) = boost::adjacent_vertices(*i, closure);
             j != j_end; ++j)
          if (*i == *j)
            rec_funs_.insert(closure[*i]);
      }
    delete graph;
  }

  // FIXME: Some code was deleted here.

} // namespace inlining
