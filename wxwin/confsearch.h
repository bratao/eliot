/* Eliot                                                                     */
/* Copyright (C) 1999  Antoine Fraboulet                                     */
/* Antoine.Fraboulet@free.fr                                                 */
/*                                                                           */
/* This program is free software; you can redistribute it and/or modify      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/* $Id: confsearch.h,v 1.1 2004/04/08 09:43:06 afrab Exp $ */

#ifndef _CONFSEARCH_H
#define _CONFSEARCH_H

#include "wx/button.h"
#include "wx/dialog.h"
#include "wx/checkbox.h"

class ConfSearchDlg : public wxDialog
{
private:
  ConfigDB config;
  
  wxButton *bok;
  wxButton *bcancel;
  
  wxCheckBox *joker_searching;
  wxCheckBox *rack_checking;

  void readconf();
  void writeconf();
  
public:

  ConfSearchDlg(wxWindow* parent);
  void OnButtonOk    (wxCommandEvent& event);
  void OnButtonCancel(wxCommandEvent& event);
  void OnCloseWindow (wxCloseEvent& event);
  
  DECLARE_EVENT_TABLE()
};
#endif