#include "sal_queue.h"

/**
 * @brief 出队列
 * 
 * @param[in] pQueHndl 队列指针
 *
 * @return
 *     @retval QueNode 节点指针
 *     @retval NULL 失败
 */
PQUE_NODE_S SAL_quePop(PQUE_HNDL_S pQueHndl)
{
    PQUE_NODE_S pQueNode = NULL;

    if (!pQueHndl || !pQueHndl->pHeadNode)
    {
        return NULL;
    }
    
    pQueNode = pQueHndl->pHeadNode;
    pQueHndl->pHeadNode = (pQueHndl->pHeadNode)->pNextNode;
    if (!pQueHndl->pHeadNode)
    {
        pQueHndl->pTailNode = NULL;
    }

    pQueHndl->cnt--;

    return pQueNode;
}

/**
 * @brief 入队列
 * 
 * @param[in] pQueHndl 队列指针
 * @param[in] pQueNode 节点指针
 *
 * @return
 *     @retval SAL_OK 成功
 *     @retval SAL_FAIL 失败
 */
INT32 SAL_quePush(PQUE_HNDL_S pQueHndl, PQUE_NODE_S pQueNode)
{    
    if (!pQueNode || !pQueHndl)
    {
        return SAL_FAIL;
    }

    pQueNode->pNextNode = NULL;
    
    if (NULL == pQueHndl->pTailNode)
    {
        pQueHndl->pHeadNode = pQueNode;
        pQueHndl->pTailNode = pQueNode;
    }
    else
    {
        (pQueHndl->pTailNode)->pNextNode = pQueNode;
        pQueHndl->pTailNode = pQueNode;
    }
    
    pQueHndl->cnt++;
    
    return SAL_OK;
}

/**
 * @brief 返回队列头节点，不从队列移开
 * 
 * @param[in] pQueHndl 队列指针
 *
 * @return
 *     @retval !NULL 成功
 *     @retval NULl 失败
 */
PQUE_NODE_S SAL_quePeep(PQUE_HNDL_S pQueHndl)
{
    if (!pQueHndl)
    {
        return NULL;
    }

    return (pQueHndl->pHeadNode);
}

/**
 * @brief 获取队列节点个数
 * 
 * @param[in] pQueHndl 队列指针
 *
 * @return
 *     @retval >=0 
 */
UINT32 SAL_queGetNodeNum(PQUE_HNDL_S pQueHndl)
{
    if (!pQueHndl)
    {
        return 0;
    }

    return pQueHndl->cnt;
}

