#include "dae.h"
//#include "dae/daeElement.h"
#include "dom/domConstants.h"
#include "dom/domCOLLADA.h"
#include "Crt/CrtTypes.h"
#include "Crt/CrtUtils.h"
#include "Crt/CrtTestInstancing.h"

// This function will check whether the suffix will make id in node all unique

// PRE: node is in the daeObject already
CrtBool IsSuffixValid(DAE *input, daeElementRef acestor, daeString suffix)
{
	daeDatabase *db = input->getDatabase();

	// Not sure whether there is id attribute
	std::string id = acestor->getAttribute("id");

	if (!id.empty())
	{
		// check whether it is fine for suffix
		if ( db->getElement( (daeElement **) &acestor, 1, (id + suffix).c_str() ) == DAE_OK )
		{
			return CrtFalse;
		}
	}

	// go through children
	daeElementRefArray elements;
	acestor->getChildren(elements);
	for (size_t i = 0; i < elements.getCount();i++)
	{
		if ( !IsSuffixValid (input, elements.get(i), suffix) )
			return CrtFalse;
	}

	return CrtTrue;
}


// This program will only show temparay instance functionality of clone of daeElement.

// We will copy whole element where node instance_parent_name has instance_node referenced for:
// For example, 
// <node id="boyShape2" name="boyShape" type="NODE">
//        <instance_node sid="test" url="#boyShape1"></instance_node>
// </node>
// put content of #bodyShape1 under it

// PRE: there is only one instance_node in it.
//		instance_parent_id
CrtBool Deref_InstancingNode(DAE *daeObject, daeString instance_parent_id, daeString suffix)
{
	// check whether any of them is zero
	if ( daeObject == NULL || CrtCmp(instance_parent_id, "") )
		return CrtFalse;

	daeUInt instance_parent_Count = daeObject->getDatabase()->getElementCount(instance_parent_id);

	for (unsigned int i = 0;i < instance_parent_Count;i++)
	{
		domNode *instance_parent;

		// get the pointer of instance_parent_name 
		daeInt error = daeObject->getDatabase()->getElement( (daeElement **)&instance_parent, i, instance_parent_id);

		if (error == DAE_OK)
		{
			// and check whether there is instance there
			daeElementRefArray elements;
			instance_parent->getChildren(elements);

			// define the pointer just before instance_node, i.e., marker pointer
			daeElement * marker = NULL;

			// check number of child
			for (size_t j = 0;j < elements.getCount();j++)
			{
				// get child element
				daeElement * e = elements.get(j);

				// find name of this element
				daeString name = e->getElementName() ? e->getElementName() : (daeString)e->getMeta()->getName();

				// find id for this child if there is an id for it
				std::string sid = e->getAttribute("sid");
				
				if (CrtCmp(name, COLLADA_ELEMENT_INSTANCE_NODE)) // when it is an instance_node
				{					
					// after find it, clone it and resolve data under it
					// Must use smart ref when functions which is allocating memory returns smart ref as well
					daeElementRef node_ptr = ((domInstance_node *)e)->getUrl().getElement();

					if (node_ptr != NULL)
					{
						daeElementRefArray node_elements;
						node_ptr->getChildren(node_elements);

						daeElementRefArray renamed_elements;

						// for each child
						for (size_t k = 0;k < node_elements.getCount();k++)
						{
							// check name or id for clone is unique
							if ( IsSuffixValid(daeObject, node_elements.get(k), suffix) )
							{
								// clone each of its child elements to current element
								renamed_elements.append( node_elements.get(k)->clone(suffix, suffix) );
							}
							else
							{
								// some id is not correct: clean the cloned objects
								renamed_elements.clear();
								// report id can not be resolve!
								CrtPrint("Error: suffix is not good for some child node id: %s.\n", node_elements.get(k)->getID() );
								return CrtFalse;
							}
						}

						// remove old instance_node of this instance_parent:
						daeBool removed = instance_parent->removeChildElement(e);

						if (removed)
						{
							// add new elements to current node:
							for (size_t k = 0;k < renamed_elements.getCount();k++)
							{
								daeBool IsInserted = (marker == NULL) ? instance_parent->placeElement(renamed_elements.get(k)):instance_parent->placeElementAfter(marker, renamed_elements.get(k));
								if ( !IsInserted )
								{
									CrtPrint("Error: element can not be placed at what it should be.\n");
									return CrtFalse;
								}
								// update marker
								marker = renamed_elements.get(k);
							}
							// resolve all element for this clone:
							daeElement::resolveAll();
							// successfully finish De-referencing
							return CrtTrue;
						}
						else
						{
							CrtPrint("Error: we can not remove this instance_node: %s.\n", sid);
							return CrtFalse;
						}			
					}
					else
					{
						CrtPrint("Error: can not find element where matches the url.\n");
						return CrtFalse;
					}
				}
				else
				{
					// update marker
					marker = e;
				}						
			}
		}
		else // else no such or can not resolve it, return false
		{
			CrtPrint("Error: can not find this element under %s.\n", instance_parent_id);
			return CrtFalse;
		}
		// output some test result?
	}

	return CrtFalse;
}

	/*
						domNodeRef new_child = daeSafeCast <domNode> ( node_ptr->clone(suffix, suffix));
						if (new_child != NULL) // successfully cast it!
						{
							// remove old child of this instance_parent:
							daeBool removed = instance_parent->removeChildElement(e);

							if (removed)
							{
								// add cloned result as new child
								bool IsPlacement = instance_parent->placeElement(new_child);
								if (IsPlacement)
								{
									// resolve all element for this clone:
									daeElement::resolveAll();
									return CrtTrue;
								}
								else
								{
									// memory allocation from smart ref (clone) will be clear by scope															
									return CrtFalse;
								}
							}
							else
							{
								CrtPrint("Error: can not remove this element.\n");
								// memory allocation from smart ref (clone) will be clear by scope
								return CrtFalse;
							}
						}
						else
						{
							CrtPrint("Error: can not clone it correctly.\n");
							return CrtFalse;
						}
						*/