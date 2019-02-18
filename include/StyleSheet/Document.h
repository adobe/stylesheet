/*
 *   Copyright 2010, Marco Ambu.
 *   Copyright 2019 Adobe Systems Incorporated
 *
 *   This file is part of StyleSheet library.
 *
 *   StyleSheet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   StyleSheet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with StyleSheet.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _CSS_CSSDOCUMENT_H
#define _CSS_CSSDOCUMENT_H

#include "StyleSheet/Element.h"
#include <boost/tokenizer.hpp>
#include <list>

namespace StyleSheet {

class CssDocument
{
public:
	CssDocument() {}
	// static ctor

	static CssDocument* parseP( const std::string& doc )
	{
		CssDocument* document = new CssDocument();
		boost::char_separator<char> sep( "\n" );
		boost::tokenizer<boost::char_separator<char> > tok( doc, sep );
		for( boost::tokenizer<boost::char_separator<char> >::iterator it = tok.begin(); it != tok.end(); ++it )
		{
			document->addElement( CssElement::parse( *it ) );
		}
		return document;
	}

	static CssDocument parse(const std::string& doc)
	{
		CssDocument document;
		boost::char_separator<char> sep("\n");
		boost::tokenizer<boost::char_separator<char> > tok(doc, sep);
		for (boost::tokenizer<boost::char_separator<char> >::iterator it = tok.begin(); it != tok.end(); ++it)
		{
			CssElement newElement = CssElement::parse(*it);
			
			if( document.hasSelector(newElement.getSelector()) )
			{
				CssElement currentElement = document.getElement(newElement.getSelector());
				currentElement.merge(newElement);

				document.removeElement(currentElement.getSelector());
				document.addElement(currentElement);
			}
			else
				document.addElement(newElement);
		}
		return document;
	}

	std::size_t getElementCount() const { return elements_.size(); }

	CssElement getElement(const CssSelector& selector) const
  {
		CssElementSet::const_iterator it = std::find_if(elements_.begin(), elements_.end(), SelectorFinder(selector));
		if (it == elements_.end())
			return CssElement(selector, CssPropertySet());
		return *it;
	}

	bool hasSelector(const CssSelector& selector) const {
		return std::find_if(elements_.begin(), elements_.end(), SelectorFinder(selector)) != elements_.end();
	}

	void addElement(const CssElement& element)
	{
    elements_.remove_if(SelectorFinder(element.getSelector()));
		if (element.getPropertyCount() == 0)
			return;
		elements_.push_back(element);
	}
  
  void removeElement(const CssSelector& selector)
  {
    elements_.remove_if(SelectorFinder(selector));
  }
  
  const std::list<CssElement>& getElements() const
  {
    return elements_;
  }

	std::string toString() const
	{
		std::string res = "";
		for (CssElementSet::const_iterator it = elements_.begin(); it != elements_.end(); ++it)
		{
			res += it->toString() + "\n";
		}
		return res;
	}

private:
	typedef std::list<CssElement> CssElementSet;
	CssElementSet elements_;

private:
	class SelectorFinder
	{
	public:
		SelectorFinder(const CssSelector& selector)
			: selector_(selector)
		{}
		SelectorFinder(const SelectorFinder& other)
			: selector_(other.selector_)
		{}
		SelectorFinder& operator=(const SelectorFinder&);	// not implemented

		bool operator()(const CssElement& element) const {
			return element.getSelector() == selector_;
		}

	private:
		const CssSelector& selector_;
	};
};

} // namespace StyleSheet

#endif // _CSS_CSSDOCUMENT_H
