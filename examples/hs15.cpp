/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *  This example demonstrates how to use Knitro to solve the following
 *  simple nonlinear optimization problem.  This model is test problem
 *  HS15 from the Hock & Schittkowski collection.
 *
 *  min   100 (x1 - x0^2)^2 + (1 - x0)^2
 *
 *  s.t.  x0 x1 >= 1
 *        x0 + x1^2 >= 0
 *
 *        x0 <= 0.5
 *
 *  The standard start point (-2, 1) usually converges to the standard
 *  minimum at (0.5, 2.0), with final objective = 306.5.
 *  Sometimes the solver converges to another local minimum
 *  at (-0.79212, -1.26243), with final objective = 360.4.
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "knitrocpp/knitro.hpp"

#include <iostream>

int main(int, char**)
{
    // Create a new Knitro context.
    knitrocpp::Context knitro_context;

    // Add variables.
    struct Variables
    {
        knitrocpp::VariableId x0;
        knitrocpp::VariableId x1;
    };
    Variables variables;
    variables.x0 = knitro_context.add_var();
    variables.x1 = knitro_context.add_var();

    // Variable bounds.
    // x0 <= 0.5
    knitro_context.set_var_upbnd(
            variables.x0,
            0.5);

    // Initial point.
    knitro_context.set_var_primal_init_value(
            variables.x0,
            -2.0);
    knitro_context.set_var_primal_init_value(
            variables.x1,
            1.0);

    // Add constraints.
    struct Constraints
    {
        knitrocpp::ConstraintId c0;
        knitrocpp::ConstraintId c1;
    };
    Constraints constraints;

    // Constraint c0.
    // x0 x1 >= 1
    constraints.c0 = knitro_context.add_con();
    knitro_context.add_con_quadratic_term(
            constraints.c0,
            variables.x0,
            variables.x1,
            1.0);
    knitro_context.set_con_lobnd(
            constraints.c0,
            1.0);

    // Constraint c1.
    // x0 + x1^2 >= 0
    constraints.c1 = knitro_context.add_con();
    knitro_context.add_con_linear_term(
            constraints.c1,
            variables.x0,
            1.0);
    knitro_context.add_con_quadratic_term(
            constraints.c1,
            variables.x1,
            variables.x1,
            1.0);
    knitro_context.set_con_lobnd(
            constraints.c1,
            0.0);

    // Objective.
    // min 100 (x1 - x0^2)^2 + (1 - x0)^2
    CB_context* callback_context = knitro_context.add_eval_callback(
            true,  // evaluate objective?
            {},  // constraints
            [&variables](
                const knitrocpp::Context&,
                CB_context*,
                KN_eval_request_ptr const eval_request,
                KN_eval_result_ptr const eval_result)
            {
                const double* x = eval_request->x;
                double tmp1 = x[variables.x1] - x[variables.x0] * x[variables.x0];
                double tmp2 = 1.0 - x[variables.x0];
                *eval_result->obj = 100.0 * (tmp1 * tmp1) + (tmp2 * tmp2);
                return 0;
            });
    knitro_context.set_cb_grad(
            callback_context,
            nullptr,
            nullptr,
            nullptr,
            [&variables](
                const knitrocpp::Context&,
                CB_context*,
                KN_eval_request_ptr const eval_request,
                KN_eval_result_ptr const eval_result)
            {
                const double* x = eval_request->x;
                double tmp = x[variables.x1] - x[variables.x0] * x[variables.x0];
                eval_result->objGrad[variables.x0]
                    = (-400.0 * tmp * x[variables.x0])
                    - (2.0 * (1.0 - x[variables.x0]));
                eval_result->objGrad[variables.x1] = 200.0 * tmp;
                return 0;
            });
    knitro_context.set_cb_hess(
            callback_context,
            nullptr,
            nullptr,
            [&variables](
                const knitrocpp::Context&,
                CB_context*,
                KN_eval_request_ptr const eval_request,
                KN_eval_result_ptr const eval_result)
            {
                const double* x = eval_request->x;
                double sigma = *(eval_request->sigma);
                // (x0, x0)
                eval_result->hess[0] = sigma * (
                        (-400.0 * x[variables.x1])
                        + (1200.0 * x[variables.x0]*x[variables.x0]) + 2.0);
                // (x0, x1)
                eval_result->hess[1] = sigma * (-400.0 * x[variables.x0]);
                // (x1, x1)
                eval_result->hess[2] = sigma * 200.0;
                return 0;
            });

    // Solve.
    int knitro_return_status = knitro_context.solve();

    // Print results.
    std::cout
        << "Return status: " << knitro_return_status << std::endl
        << "Objective value: " << knitro_context.get_obj_value() << std::endl
        << "Absolute feasibility error: " << knitro_context.get_abs_feas_error() << std::endl
        << "Relative feasibility error: " << knitro_context.get_rel_feas_error() << std::endl
        << "Absolute optimality error: " << knitro_context.get_abs_opt_error() << std::endl
        << "Relative optimality error: " << knitro_context.get_rel_opt_error() << std::endl
        << "x0: " << knitro_context.get_var_primal_value(variables.x0) << std::endl
        << "x1: " << knitro_context.get_var_primal_value(variables.x1) << std::endl
        ;
}
