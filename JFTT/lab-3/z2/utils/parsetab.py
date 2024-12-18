
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = 'leftADDSUBleftMULDIVnonassocPOWADD DIV LEFT MUL NEWLINE NUMBER POW RIGHT SUBexpression : NEWLINEexpression : expression NEWLINEexpression : NUMBERexpression : SUB NUMBERexpression : expression ADD expression\n                  | expression SUB expression\n                  | expression MUL expression\n                  | expression DIV expression\n                  | expression POW expressionexpression : LEFT expression RIGHT'
    
_lr_action_items = {'NEWLINE':([0,1,2,3,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,],[2,6,-1,-3,2,-2,2,2,2,2,2,-4,6,-5,-6,-7,-8,-9,-10,]),'NUMBER':([0,4,5,7,8,9,10,11,],[3,12,3,3,3,3,3,3,]),'SUB':([0,1,2,3,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,],[4,8,-1,-3,4,-2,4,4,4,4,4,-4,8,-5,-6,-7,-8,-9,-10,]),'LEFT':([0,5,7,8,9,10,11,],[5,5,5,5,5,5,5,]),'$end':([1,2,3,6,12,14,15,16,17,18,19,],[0,-1,-3,-2,-4,-5,-6,-7,-8,-9,-10,]),'ADD':([1,2,3,6,12,13,14,15,16,17,18,19,],[7,-1,-3,-2,-4,7,-5,-6,-7,-8,-9,-10,]),'MUL':([1,2,3,6,12,13,14,15,16,17,18,19,],[9,-1,-3,-2,-4,9,9,9,-7,-8,-9,-10,]),'DIV':([1,2,3,6,12,13,14,15,16,17,18,19,],[10,-1,-3,-2,-4,10,10,10,-7,-8,-9,-10,]),'POW':([1,2,3,6,12,13,14,15,16,17,18,19,],[11,-1,-3,-2,-4,11,11,11,11,11,None,-10,]),'RIGHT':([2,3,6,12,13,14,15,16,17,18,19,],[-1,-3,-2,-4,19,-5,-6,-7,-8,-9,-10,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'expression':([0,5,7,8,9,10,11,],[1,13,14,15,16,17,18,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> expression","S'",1,None,None,None),
  ('expression -> NEWLINE','expression',1,'p_empty','parser.py',30),
  ('expression -> expression NEWLINE','expression',2,'p_expression_newline','parser.py',34),
  ('expression -> NUMBER','expression',1,'p_expression_number','parser.py',41),
  ('expression -> SUB NUMBER','expression',2,'p_expression_sub_number','parser.py',46),
  ('expression -> expression ADD expression','expression',3,'p_expression_binop','parser.py',51),
  ('expression -> expression SUB expression','expression',3,'p_expression_binop','parser.py',52),
  ('expression -> expression MUL expression','expression',3,'p_expression_binop','parser.py',53),
  ('expression -> expression DIV expression','expression',3,'p_expression_binop','parser.py',54),
  ('expression -> expression POW expression','expression',3,'p_expression_binop','parser.py',55),
  ('expression -> LEFT expression RIGHT','expression',3,'p_expression_group','parser.py',70),
]
