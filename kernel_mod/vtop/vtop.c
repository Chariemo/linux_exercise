#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/pid.h>
#include <linux/sched.h>

static int pid;

module_param(pid, int, 0644);



static struct page * my_follow_page(struct vm_area_struct * vma, unsigned long addr) {
    pud_t * pud;
    pmd_t * pmd;
    pte_t * pte;
    pgd_t * pgd;
    spinlock_t *ptl;
    unsigned long full_addr;
    struct page * page = NULL;
    struct mm_struct * mm = vma -> vm_mm;

    pgd = pgd_offset(mm, addr);
    if(pgd_none(*pgd) || unlikely(pgd_bad(*pgd))) {
        goto out;
    }

    pud = pud_offset(pgd, addr);
    if(pud_none(*pud) || unlikely(pud_bad(*pud))) {
        goto out;
    }
    pmd = pmd_offset(pud, addr);
    if(pmd_none(*pmd) || unlikely(pmd_bad(*pmd))) {
        goto out;
    }

    pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
    if(!pte)
        goto out;

    if(!pte_present(*pte))
        goto unlock;

    page = pfn_to_page(pte_pfn(*pte));
    if(!page)
        goto unlock;

    full_addr = (*pte).pte & PAGE_MASK;
    full_addr += addr & (~PAGE_MASK);
    printk("full_addr = %lx\n", full_addr);
    printk("pte = %lx\n", pte_pfn(*pte));
    printk("page = %p\n", page);

    get_page(page);

unlock:
    pte_unmap_unlock(pte, ptl);
out:
    return page;
}

static int __init memtest_init(void) {
    struct task_struct *p;
    struct vm_area_struct *temp;
    struct page * pg = NULL;
    p = pid_task(find_vpid(pid), PIDTYPE_PID);
    temp = p -> mm -> mmap;

    pg = my_follow_page(temp, temp -> vm_start);

    printk("v to p succeed.\n");

    return 0;
}

static void __exit memtest_exit(void) {
    printk("Unloading my module.\n");
    return;
}

module_init(memtest_init);
module_exit(memtest_exit);
MODULE_LICENSE("GPL");
