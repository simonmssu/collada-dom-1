#include "dae.h"
//#include "dae/daeElement.h"
#include "dom/domConstants.h"
#include "dom/domCOLLADA.h"
#include "Crt/CrtTypes.h"
#include "Crt/CrtUtils.h"
#include "Crt/CrtTestInstancing.h"

// This function will check whether the suffix will make id in node all unique

// PRE: node is in the daeObject already
CrtBool IsSuffixValid(DAE *input, const daeElementRef acestor, const daeString suffix)
{
	daeDatabase *db = input->getDatabase();

	// Not sure whether there is id attribute
	std::string id = acestor->getAttribute("id");

	daeElementRef tmp;

	if (!id.empty())
	{
		// check whether it is fine for suffix
		if ( db->getElement( (daeElement **) &tmp, 1, (id + suffix).c_str() ) == DAE_OK )
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
CrtBool Deref_InstancingNode(DAE *daeObject, const daeString instance_parent_id, const daeString suffix)
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

			// check children: look for child element
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
					// resolve Url fisrt
					daeElementRef node_ptr = ((domInstance_node *)e)->getUrl().getElement();

					if (node_ptr != NULL)
					{
						// Must use smart ref when functions which is allocating memory returns smart ref as well
						domNodeRef new_child;
						
						if (IsSuffixValid(daeObject, node_ptr, suffix))
						{
							// remove old instance_node of this instance_parent:
							daeBool removed = instance_parent->removeChildElement(e);

							if (removed)
							{
								// after find it, clone it and resolve data under it
								new_child = daeSafeCast <domNode> ( node_ptr->clone(suffix, suffix));

								// add new elements to current node:
								// add cloned result as new child
								bool IsPlacement = instance_parent->placeElement(new_child);
								if (IsPlacement)
								{
									// resolve all element for this clone:
									daeElement::resolveAll();
									// successfully finish De-referencing
									return CrtTrue;
								}
								else
								{
									CrtPrint("Can not insert current node.\n");
									// memory allocation from smart ref (clone) will be clear by scope															
									return CrtFalse;
								}
							}
							else
							{
								CrtPrint("Error: we can not remove this instance_node: %s.\n", sid);
								return CrtFalse;
							}			
						}
						else
						{
							CrtPrint("Error: suffix can not produce unique id.\n");
							return CrtFalse;
						}
					}
					else
					{
						CrtPrint("Error: can not find element where matches the url.\n");
						return CrtFalse;
					}
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