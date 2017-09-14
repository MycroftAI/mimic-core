/*******************************************************/
/**  Autogenerated cart trees for us_phrasing    */
/*******************************************************/

#include "cst_synth.h"
#include "cst_string.h"
#include "cst_cart.h"
#include "cst_regex.h"
#include "us_phrasing_cart.h"

static const cst_cart_node us_phrasing_cart_nodes[] = {
{ 0, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0000, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 1, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0002, (cst_val *)&val_0002},
{ 2, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0003, (cst_val *)&val_0003},
{ 3, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0004, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 4, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0006, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0005 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 5, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0010, (cst_val *)&val_0002},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 4, CST_CART_OP_IS, CTNODE_us_phrasing_NO_0012, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0005 },
{ 255, CST_CART_OP_NONE, 0, 0}};



static const char * const us_phrasing_feat_table[] = {
"R:Token.parent.n.name",
"R:Token.n.name",
"R:Token.parent.punc",
"R:Token.parent.break",
"break",
"n.name",
NULL };

const cst_cart us_phrasing_cart = {
  us_phrasing_cart_nodes,
  us_phrasing_feat_table
};
