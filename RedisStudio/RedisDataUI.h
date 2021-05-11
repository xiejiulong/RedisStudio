﻿#pragma once
#include <memory.h>
#include "stdafx.h"
#include <string>
#include <set>
#include <list>

#include "Base/Event.h"
#include "Base/Thread.h"
#include "Base/RunnableAdapter.h"

#include "AbstractUI.h"
#include "Redis/RedisResult.h"

#include "DuiEx/UIMenu.h"

class CTreeView;

struct TreeKeyContactData
{    
    CTreeNodeUI* pPNode;
    CTreeNodeUI* pNode;
};

class RedisDataUI : public AbstraceUI
{
public:
    typedef std::map< std::string, void * > TkeyTree;

    struct RedisDataStruct
    {
        int        db;
        CDuiString key;
        CDuiString type;
        CDuiString size;
        CDuiString ttl;
        RedisResult result;
    };

    RedisDataUI(const CDuiString& strXML, CPaintManagerUI* pm, Environment* env);

    ~RedisDataUI();

    void Initialize();

    int  GetIndex();
    
    CDuiString GetVirtualwndName();

    void RefreshWnd();

    virtual bool CanChange();

    virtual LRESULT HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

    DUI_DECLARE_MESSAGE_MAP()

    virtual void OnClick(TNotifyUI& msg);

    virtual void OnItemClick( TNotifyUI &msg );

    virtual void OnItemDBClick( TNotifyUI &msg );

    virtual void OnItemActive( TNotifyUI &msg );

    virtual void OnMenuWakeup( TNotifyUI &msg );

    void    OnItemActiveForTree( TNotifyUI &msg );

    void    OnItemActiveForList( TNotifyUI &msg );

    void    OnPaginate(TNotifyUI& msg);

    void    OnCommit(TNotifyUI& msg);


    LRESULT OnDataAdd(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnDBAdd(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyAdd(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyDel(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyVerbose(HWND hwnd, WPARAM wParam, LPARAM lParam);

    LRESULT OnDataVerbose(HWND hwnd, WPARAM wParam, LPARAM lParam);

    bool    OnMenuClick( void* param );
private:    
    void    SetPageValues();

    std::size_t  GetMaxPage();

    void  SetRichEditText(const std::string& text);

    bool  TryJsonFomat(std::string& text);

    bool  TryXMLFormat(std::string& text);

    bool  TryHexFormat(std::string& text);

    RedisResult& GetResult();

public:
    void    DoRefreshDBWork();

    void    DoPaginateWork();

    void    DoRefreshKeysWork();

    void    DoRefreshValuesWork();

    void    BackgroundWorkForRefreshDB(void);

    void    BackgroudWorkForRenderLevel(void);

    void    BackgroundWorkForRefreshKeys(void);

    void    BackgroundWorkForRefreshValues(void);

private:
    void ReleaseObject(std::size_t idx);

    CTreeNodeUI* NewNode(const string& text, bool isLeaf=false);

    void         DelChildNode(CTreeNodeUI* pNode);

private:
    CListUI* m_pList;
    CHorizontalLayoutUI* m_pHorizontalLayout;
    CEditUI*         m_pKeyEdit;
    CEditUI*         m_PTypeEdit;
    CEditUI*         m_pDataSizeEdit;
    CEditUI*         m_pTTLEdit;

    CEditUI*         m_pPageCur;
    CEditUI*         m_pPageTotal;
    CButtonUI*       m_pPageFrist;
    CButtonUI*       m_pPageLast;
    CButtonUI*       m_pPageNext;
    CButtonUI*       m_pPageFinal;
    CButtonUI*       m_pCommit;
    CComboUI*        m_pComboFormat;

    CRichEditUI*     m_pRichEdit;
    CTreeNodeUI*     m_pServerInfoNode;

    Base::Event      m_oEventListHeader;
    Base::Event      m_oEventKey;
    Base::Event      m_oEventDB;

    bool             m_bIsKeyRender; 

    static const std::size_t          m_iPageSize = 100;
    std::vector<std::list<TkeyTree*>> m_oObjPool;
    std::vector<TkeyTree>             m_oKeyRoot;
    CTreeNodeUI*     m_pRootNode;
    CTreeNodeUI*     m_pAssistNode;  
    RedisDataStruct  m_oRedisData;
    Base::Thread     m_oThread;
    std::set<int>    m_setUpdateDbs;
    std::shared_ptr<Base::RunnableAdapter<RedisDataUI> > m_pWork;
    int              m_iDBIdx;
};